# Compiler for the Ç Language

## 📋 Project Description

This repository contains the complete implementation of a compiler for **Ç**, an imperative language with specific purposes designed for the **x86_64** architecture. The project constitutes an educational and fully functional implementation of a modern compiler that integrates lexical analysis, syntactic analysis, semantic analysis, and machine code generation.

The compiler follows the classic compiler architecture, dividing the process into multiple phases:

- **Front-end**: Lexical and syntactic analysis with abstract syntax tree (AST) generation
- **Semantic analysis**: Type checking and symbol table management
- **Optimization**: Intermediate code optimization techniques
- **Back-end**: x86_64 machine code generation

---

**Disponible en otros idiomas:** [Español](README.md)

##  Project Composition

```
C++ Language:     74.9%  | Main compiler logic
Yacc (Bison):     13.7%  | Syntactic analysis
Assembly (NASM):   9.7%  | Generated code for x86_64
Lex (Flex):        1.3%  | Lexical analysis
Shell:             0.4%  | Build and execution scripts
```

##  Tools and Dependencies

### System Requirements

The compiler requires the following tools to operate:

| Tool | Purpose | Minimum Version |
|------|---------|-----------------|
| **G++** | C++ Compiler | 7.0+ |
| **GCC** | C Compiler | 7.0+ |
| **Flex** | Lexical Analyzer | 2.6+ |
| **Bison** | Parser Generator | 3.0+ |
| **NASM** | x86_64 Assembler | 2.13+ |
| **Bash** | Shell Interpreter | 4.0+ |

### Installing Dependencies

#### Ubuntu/Debian:
```bash
sudo apt-get install build-essential flex bison nasm
```

#### macOS (Homebrew):
```bash
brew install flex bison nasm gcc
```

#### Fedora/RHEL:
```bash
sudo dnf install gcc g++ flex bison nasm
```

## 📁 Repository Structure

```
Compiler/
├── Codigo/                          # Main source code directory
│   ├── lexico.l                     # Lexical definitions (Flex)
│   ├── parser.y                     # Language grammar (Bison)
│   ├── main.cpp                     # Compiler entry point
│   ├── taula_simbols.h/cpp          # Symbol table
│   ├── generador_tres_dir.h         # Three-address intermediate code generator
│   ├── generador_x64.h              # x86_64 code generator
│   ├── optimizacion.h               # Code optimizations
│   ├── compilar_x64.sh              # Compiler compilation script
│   ├── compilar_y_ejecutar.sh       # Script to compile and execute Ç programs
│   ├── flex_bison.sh                # Script to regenerate lexer/parser
│   ├── test_*.txt                   # Test cases
│   └── codi_prova.txt               # Sample test program
├── Output casos de prueba/          # Test execution results
└── README.en.md                     # This file
```

##  Usage Guide

### 1. Initial Setup

First, clone the repository and navigate to the code directory:

```bash
git clone https://github.com/vroig0x04/Compiler.git
cd Compiler/Codigo
```

### 2. Execute Permissions

You must grant execute permissions to the scripts:

```bash
chmod +x compilar_x64.sh
chmod +x compilar_y_ejecutar.sh
chmod +x flex_bison.sh  # Optional, only if you need to regenerate the parser
```

### 3. Compiler Compilation

To compile the compiler for the first time:

```bash
./compilar_x64.sh
```

This script will generate the `mi_parser` executable, which is the functional compiler.

### 4. Compile and Execute Ç Programs

To compile a program written in the Ç language:

```bash
./compilar_y_ejecutar.sh <filename>
```

**Example:**

```bash
./compilar_y_ejecutar.sh codi_prova.txt
```

This command:
1. Compiles the program `codi_prova.txt` using the compiler
2. Generates x86_64 assembly code
3. Assembles and links the code
4. Executes the resulting program

### 5. Regenerate the Parser (Optional)

If you modify the language grammar in `parser.y` or the lexicon in `lexico.l`, you must regenerate the parser:

```bash
./flex_bison.sh
```

Then, recompile the compiler:

```bash
./compilar_x64.sh
```

##  Ç Language Syntax Basics

The repository includes several test cases demonstrating the syntax:

- **test_basic.txt**: Basic operations and variables
- **test_control.txt**: Control structures (if, while, for)
- **test_funcions.txt**: Function definition and invocation
- **test_tuples.txt**: Tuple handling
- **test_errors_tipus.txt**: Type validation and error handling

Consult these files for examples of supported syntax.

##  Test Cases

The project includes a comprehensive test suite that validates:

-  Lexical and syntactic analysis
-  Type checking
-  Correct code generation
-  Semantic error handling
-  Basic and advanced operations

Execution results are stored in the `Output casos de prueba/` directory.

##  Compiler Phases

### Phase 1: Lexical Analysis
Performed by **Flex** via `lexico.l`, tokenizes the source code.

### Phase 2: Syntactic Analysis
Performed by **Bison** via `parser.y`, constructs the abstract syntax tree (AST).

### Phase 3: Semantic Analysis
Implemented in C++, validates types and maintains the symbol table via `taula_simbols`.

### Phase 4: Intermediate Code Generation
Three-address code generator (`generador_tres_dir.h`) for optimizations.

### Phase 5: Optimization
Module `optimizacion.h` applies optimizations to the intermediate code.

### Phase 6: Machine Code Generation
x86_64 generator (`generador_x64.h`) produces NASM assembly code.

### Phase 7: Assembly and Linking
Performed by **NASM** and **GCC**, generates the final executable.

##  x86_64 Architecture

The compiler generates optimized code for the x86_64 architecture following system calling conventions. The generated code is compatible with Linux/Unix systems based on x86_64.

## ⚠️ License and Copyright

This software is the intellectual property of **Vicent Roig**. Unauthorized copying, modification, or distribution of this file, via any medium, is strictly prohibited.

## 🤝 Contributing

Contributions are not accepted at this time given the proprietary nature of the project.

## 📞 Contact

For inquiries related to this project, please contact the repository owner.

---

**Last Updated:** September 2026  
**Compiler Version:** 1.0  
**Supported Architecture:** x86_64 (64-bit)
