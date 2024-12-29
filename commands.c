/* commands.c */
/* Copyright (c) 2025 C. J. Wilson */

#include "commands.h"
#include "lib.h"  // For atoi, strcmp, and printf
#include "hardware.h" // If needed for other operations

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



void execute_command(char *cmd) {
    char op[16];
    int a = 0, b = 0, result = 0;
    char *p = cmd;

    // Extract the operation
    char *op_ptr = op;
    while (*p != ' ' && *p != '\0' && op_ptr < op + sizeof(op) - 1) {
        *op_ptr++ = *p++;
    }
    *op_ptr = '\0';

    // Skip spaces
    while (*p == ' ') p++;

	if (strcmp(op, "HELP") == 0) {
		printf("Supported commands:\n");
		printf("  ADD <a> <b>   : Add two numbers\n");
		printf("  SUB <a> <b>   : Subtract two numbers\n");
		printf("  MUL <a> <b>   : Multiply two numbers\n");
		printf("  DIV <a> <b>   : Divide two numbers\n");
		printf("  MOD <a> <b>   : Remainder of a divided by b\n");
		printf("  POW <a> <b>   : a raised to the power of b\n");
		printf("  EQ <a> <b>    : Check if a equals b\n");
		printf("  NEQ <a> <b>   : Check if a is not equal to b\n");
		printf("  GT <a> <b>    : Check if a is greater than b\n");
		printf("  LT <a> <b>    : Check if a is less than b\n");
		printf("  GTE <a> <b>   : Check if a is greater or equal to b\n");
		printf("  LTE <a> <b>   : Check if a is less or equal to b\n");
		printf("  HELP          : Show this help message\n");
		return;
	}

    // Parse numbers
    a = atoi(p);
    while (*p >= '0' && *p <= '9') p++;
    while (*p == ' ') p++;
    b = atoi(p);

// Perform the operation
if (strcmp(op, "ADD") == 0) {
    result = func_add(a, b);
} else if (strcmp(op, "SUB") == 0) {
    result = func_sub(a, b);
} else if (strcmp(op, "MUL") == 0) {
    result = func_mul(a, b);
} else if (strcmp(op, "DIV") == 0) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return;
    }
    result = func_div(a, b);
} else if (strcmp(op, "MOD") == 0) {
    result = func_mod(a, b);
} else if (strcmp(op, "POW") == 0) {
    result = func_pow(a, b);
} else if (strcmp(op, "EQ") == 0) {
    result = func_eq(a, b);
} else if (strcmp(op, "NEQ") == 0) {
    result = func_neq(a, b);
} else if (strcmp(op, "GT") == 0) {
    result = func_gt(a, b);
} else if (strcmp(op, "LT") == 0) {
    result = func_lt(a, b);
} else if (strcmp(op, "GTE") == 0) {
    result = func_gte(a, b);
} else if (strcmp(op, "LTE") == 0) {
    result = func_lte(a, b);
} else {
    printf("Unknown command: %s\n", op);
    return;
}

// Output the result
printf("Result: %d\n", result);

}
