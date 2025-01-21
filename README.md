# Minishell  

**Minishell** is a simplified Unix-like shell implemented in C. This project replicates core functionalities of a command-line interpreter, including parsing user input, executing commands, and managing processes. It demonstrates a deep understanding of how shells work and interact with the operating system.  

## Features  
- **Prompt**: Displays a prompt and reads user input.  
- **Command Execution**: Executes both built-in commands and external programs.  
- **Pipes**: Supports piping to chain multiple commands (e.g., `ls | grep txt`).  
- **Redirections**: Handles input (`<`), output (`>`), append (`>>`), and heredoc (`<<`) redirections.  
- **Signal Handling**: Captures and handles signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`, mimicking Bash behavior.  
- **Built-in Commands**: Implements basic commands such as:  
  - `cd`  
  - `echo` (with `-n` option)  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`  

## What I Learned  
- **System Calls**: Worked extensively with `fork`, `execve`, `pipe`, `dup2`, and signal handling functions (`signal`, `sigaction`) to manage processes and file descriptors. 
- **Process Management**: Gained experience in creating and synchronizing child processes.  
- **Signal Handling**: Learned how to intercept and handle terminal signals to control shell behavior.  
- **Error Handling**: Implemented robust error detection for invalid commands and system call failures.  

## Technologies  
- **Language**: C  
- **Libraries**: Standard C library and POSIX system calls  

## Acknowledgments  
This project was a challenging yet rewarding exploration of shell behavior, deepening my understanding of system programming, process management, and Unix-like environments. 

## Usage

1. Clone the repository:
   ```bash
   git clone git@github.com:tahakerroumi/minishell.git
   cd minishell
2. Compile the program using make
   ```bash
   make
3. Run the program
   ```bash
   ./minishell
