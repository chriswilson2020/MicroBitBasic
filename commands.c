#include "commands.h"
#include "lib.h"

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

// Wrapper for division to handle divide-by-zero
int safe_div(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return func_div(a, b);
}

// Command lookup table
static const command_entry commands[] = {
    {"ADD", func_add},
    {"SUB", func_sub},
    {"MUL", func_mul},
    {"DIV", safe_div}, // Use safe division
    {"MOD", func_mod},
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
    
    // Check for HELP command
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
        printf("  HELP          : Show this help message\n");
        return;
    }

    // Skip spaces
    while (*p == ' ') p++;

    // Parse operands
    a = atoi(p);
    while (*p >= '0' && *p <= '9') p++;
    while (*p == ' ') p++;
    b = atoi(p);

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

