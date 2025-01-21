# Minishell  

**Minishell** is a simplified Unix-like shell implemented in C. This project replicates core functionalities of a command-line interpreter, including parsing user input, executing commands, and managing processes. It demonstrates a deep understanding of how shells work and interact with the operating system.  

## Features  
- **Prompt**: Displays a prompt and reads user input.  
- **Command Execution**: Executes both built-in commands and external programs.  
- **Pipes**: Supports piping to chain multiple commands (e.g., `ls | grep txt`).  
- **Redirections**: Handles input (`<`), output (`>`), and append (`>>`) redirections.  
- **Built-in Commands**: Implements basic commands such as:  
  - `cd`  
  - `echo` (with `-n` option)  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`  

## What I Learned  
- **System Calls**: Worked extensively with `fork`, `execve`, `pipe`, and `dup2` to manage processes and file descriptors.  
- **Parsing**: Developed logic to handle complex input structures, including pipes and redirections.  
- **Process Management**: Gained experience in creating and synchronizing child processes.  
- **Error Handling**: Implemented robust error detection for invalid commands and system call failures.  

## Technologies  
- **Language**: C  
- **Libraries**: Standard C library and POSIX system calls  

## Acknowledgments  
This project was a challenging yet rewarding exploration of shell behavior, deepening my understanding of system programming and Unix-like environments.  
