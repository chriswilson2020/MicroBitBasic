#include "commands.h"
#include "lib.h"

#define MAX_VARIABLES 26 // Variables A-Z

typedef struct {
    char name;
    int value;
    int is_set; // Flag to check if the variable is initialized
} variable_t;

static variable_t variables[MAX_VARIABLES];

typedef int (*command_fn)(int, int);

typedef struct {
    const char *name;
    command_fn func;
} command_entry;

// Command function prototypes
extern int func_add(int a, int b);
extern int func_sub(int a, int b);
extern int func_mul(int a, int b);
extern int func_div(int a, int b);
extern int func_mod(int a, int b);
extern int func_pow(int base, int exp);
extern int func_eq(int a, int b);
extern int func_neq(int a, int b);
extern int func_gt(int a, int b);
extern int func_lt(int a, int b);
extern int func_gte(int a, int b);
extern int func_lte(int a, int b);

void initialize_variables() {
    for (int i = 0; i < MAX_VARIABLES; i++) {
        variables[i].name = 'A' + i;
        variables[i].value = 0;
        variables[i].is_set = 0; // Mark as unset
    }
}


// Wrapper for division to handle divide-by-zero
int safe_div(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return func_div(a, b);
}

int safe_mod(int a, int b) {
    // printf("DEBUG: safe_mod called with a = %d, b = %d\n", a, b);
    if (b == 0) {
        printf("Error: Division by zero in MOD operation\n");
        return 0;
    }
    int result = func_mod(a, b);
    // printf("DEBUG: func_mod result = %d\n", result);
    return result;
}


void set_variable(char var_name, int value) {
    if (var_name < 'A' || var_name > 'Z') {
        printf("Error: Invalid variable name '%c'. Use A-Z.\n", var_name);
        return;
    }

    int index = var_name - 'A';
    variables[index].value = value;
    variables[index].is_set = 1; // Mark as initialized
    printf("%c = %d\n", var_name, value);
}

int get_variable(char var_name) {
    if (var_name < 'A' || var_name > 'Z') {
        printf("Error: Invalid variable name '%c'. Use A-Z.\n", var_name);
        return 0;
    }

    int index = var_name - 'A';
    if (!variables[index].is_set) {
        printf("Error: Variable '%c' is not initialized.\n", var_name);
        return 0;
    }

    return variables[index].value;
}


// Command lookup table
static const command_entry commands[] = {
    {"ADD", func_add},
    {"SUB", func_sub},
    {"MUL", func_mul},
    {"DIV", safe_div}, // Use safe division
    {"MOD", safe_mod},
    {"POW", func_pow},
    {"EQ", func_eq},
    {"NEQ", func_neq},
    {"GT", func_gt},
    {"LT", func_lt},
    {"GTE", func_gte},
    {"LTE", func_lte},
    {NULL, NULL}  // End of table
};

void execute_command(const char *cmd) {
    char op[16];
    int a = 0, b = 0, result = 0;
    char *p = (char *)cmd;

    // Extract operation
    char *op_ptr = op;
    while (*p != ' ' && *p != '\0' && op_ptr < op + sizeof(op) - 1) {
        *op_ptr++ = *p++;
    }
    *op_ptr = '\0';

    // Handle HELP command
    if (strcmp(op, "HELP") == 0) {
        printf("Supported commands:\n");
        printf("  ADD <a> <b>   : Add two numbers\n");
        printf("  SUB <a> <b>   : Subtract the second number from the first\n");
        printf("  MUL <a> <b>   : Multiply two numbers\n");
        printf("  DIV <a> <b>   : Divide the first number by the second\n");
        printf("  MOD <a> <b>   : Remainder of a divided by b\n");
        printf("  POW <a> <b>   : a raised to the power of b\n");
        printf("  EQ <a> <b>    : Check if two numbers are equal\n");
        printf("  NEQ <a> <b>   : Check if two numbers are not equal\n");
        printf("  GT <a> <b>    : Check if the first number is greater than the second\n");
        printf("  LT <a> <b>    : Check if the first number is less than the second\n");
        printf("  GTE <a> <b>   : Check if the first number is greater than or equal to the second\n");
        printf("  LTE <a> <b>   : Check if the first number is less than or equal to the second\n");
        printf("  LET <var> <value> : Assign a value to a variable (A-Z)\n");
        printf("  HELP          : Show this help message\n");
        return;
    }

    // Handle LET command
    if (strcmp(op, "LET") == 0) {
        while (*p == ' ') p++; // Skip spaces
        char var_name = *p++;
        if (var_name < 'A' || var_name > 'Z') {
            printf("Error: Invalid variable name '%c'. Use A-Z.\n", var_name);
            return;
        }
        while (*p == ' ') p++; // Skip spaces
        int value = atoi(p);
        set_variable(var_name, value);
        return;
    }

    // Handle variable reference as command
    if (op[0] >= 'A' && op[0] <= 'Z' && op[1] == '\0') {
        result = get_variable(op[0]);
        printf("%c = %d\n", op[0], result);
        return;
    }

    // Skip spaces
    while (*p == ' ') p++;

    // Parse the first operand
    if (*p >= 'A' && *p <= 'Z') {
        a = get_variable(*p++); // Get the value of the variable
    } else {
        a = atoi(p); // Parse as an integer
        while (*p >= '0' && *p <= '9') p++;
    }

    while (*p == ' ') p++; // Skip spaces

    // Parse the second operand
    if (*p >= 'A' && *p <= 'Z') {
        b = get_variable(*p++); // Get the value of the variable
    } else {
        b = atoi(p); // Parse as an integer
        while (*p >= '0' && *p <= '9') p++;
    }
    
    // printf("DEBUG: a = %d, b = %d\n", a, b);


    // Lookup command in the table
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(op, commands[i].name) == 0) {
            result = commands[i].func(a, b);
            printf("Result: %d\n", result);
            return;
        }
    }

    // Command not found
    printf("Unknown command: %s\n", op);
}
