# Minishell

Minishell is a simplified Unix shell implementation, built as a programming project. It provides a command-line interface that allows users to interact with the operating system by executing commands.

This project aims to recreate a subset of the functionalities found in a traditional Unix shell. It serves as an exercise in systems programming and provides an opportunity to understand the inner workings of a shell environment.


## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Conclusion](#conclusion) 


## Features

- Command Parsing: Minishell parses user input to identify and interpret commands, arguments, and options.
- Process Management: It handles process creation, execution, and termination, allowing users to run commands and external programs.
- Built-in Commands: The shell supports a set of built-in commands, such as `cd` for changing directories and `exit` for terminating the shell.
- Redirection and Pipes: Minishell supports input/output redirection, allowing users to redirect input and output streams. It also enables the piping of commands, allowing the output of one command to serve as input to another.
- Environment Variables: The shell supports the creation and management of environment variables.
- Signal Handling: Minishell handles signals such as `Ctrl-C` and `Ctrl-\` to terminate or suspend the shell.

## Installation

1. Clone the repo
   ```sh
   git clone https://github.com/your_username_/minishell.git
    ```
2. Make sure to install the readline library
   ```sh
   brew install readline
   ```
   and set the path to the library in the Makefile
   ```sh
    LD_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
    INC_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include
    ```
3. Run make


## Conclusion

This project serves as an educational tool to deepen understanding of fundamental operating system concepts, process management, and command-line interfaces. By implementing a subset of shell functionalities, users can gain hands-on experience and enhance their programming skills in a system-level environment.

Please note that while Minishell aims to replicate some features of a real shell, it may not support the entire range of complex features found in production-level shells like Bash or Zsh.
