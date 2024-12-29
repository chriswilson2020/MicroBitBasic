# Micro:bit BASIC Interpreter

This project implements a simple BASIC-like interpreter for the Micro:bit V2. It features a REPL (Read-Eval-Print Loop) that allows users to perform basic arithmetic operations, comparisons, and more, using a minimalistic environment. The core functionality is written in C for input/output and control flow, while the computational operations are implemented in ARM Cortex-M4 assembly for optimal performance.

This project is inspired by and builds upon the work in [baremetal-v2](https://github.com/Spivoxity/baremetal-v2), authored by J. M. Spivey.

---

## Features

### Supported Commands

- **Arithmetic Operations**:
  - `ADD <a> <b>`: Add two numbers.
  - `SUB <a> <b>`: Subtract the second number from the first.
  - `MUL <a> <b>`: Multiply two numbers.
  - `DIV <a> <b>`: Divide the first number by the second.
  - `MOD <a> <b>`: Compute the remainder of the division.
  - `POW <a> <b>`: Raise the first number to the power of the second.

- **Comparison Operations**:
  - `EQ <a> <b>`: Check if two numbers are equal.
  - `NEQ <a> <b>`: Check if two numbers are not equal.
  - `GT <a> <b>`: Check if the first number is greater than the second.
  - `LT <a> <b>`: Check if the first number is less than the second.
  - `GTE <a> <b>`: Check if the first number is greater than or equal to the second.
  - `LTE <a> <b>`: Check if the first number is less than or equal to the second.

- **Help Command**:
  - `HELP`: Display a list of supported commands with descriptions.

---

## Requirements

### Hardware
- Micro:bit V2

### Software
- GCC ARM Embedded Toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-as`, `arm-none-eabi-ld`)
- A terminal emulator (e.g., `minicom`) to interface with the REPL.

---

## Build Instructions

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. Build the project:
   ```bash
   make
   ```

3. Flash the generated `.hex` file to the Micro:bit:
   ```bash
   cp func.hex /media/<username>/MICROBIT
   ```

---

## Usage

1. Connect the Micro:bit to your computer via USB.
2. Open a terminal emulator and connect to the Micro:bit's serial port:
   ```bash
   minicom -D /dev/ttyACM0 -b 9600
   ```
3. Use the REPL to execute commands.
   - Example:
     ```
     > ADD 3 5
     Result: 8
     > GT 10 7
     Result: 1
     ```

---

## File Structure

- `fmain.c`: Contains the main REPL loop.
- `commands.c`: Handles command parsing and execution.
- `commands.h`: Header file for command handling.
- `lib.c`: Provides utility functions such as `atoi` and `strcmp`.
- `lib.h`: Header file for utility functions.
- `func.s`: Contains ARM assembly implementations of arithmetic and comparison operations.
- `startup.c`: Initializes the hardware.
- `device.ld`: Linker script for memory mapping.
- `Makefile`: Build instructions for the project.

---

## Roadmap

### Current Features
- Arithmetic operations.
- Comparison operators.
- Help system.

### Future Enhancements
- Refactor if else into a command dispatcher
- Variable assignment (`LET X = <value>`).
- Input and output enhancements (`INPUT`, `PRINT`).
- Control flow (`IF`, `GOTO`, `FOR`, `NEXT`).
- String manipulation.
- Advanced math functions (`SIN`, `COS`, `LOG`).

---

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to suggest improvements or add new features.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Acknowledgments

Special thanks to the Micro:bit Foundation for providing an accessible platform for embedded programming and education.

This project builds on the work of [baremetal-v2](https://github.com/Spivoxity/baremetal-v2), authored by J. M. Spivey.
