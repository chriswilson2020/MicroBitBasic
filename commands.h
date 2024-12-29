/* commands.h */
/* Copyright (c) 2025 C. J. Wilson */


#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_VARIABLES 26 // Variables A-Z

// Function to initialize variables
void initialize_variables(void);

// Function to execute a command
void execute_command(const char *cmd);

#endif // COMMANDS_H
