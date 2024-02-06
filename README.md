# Minishell  
**As beautiful as a shell**  

## Overview  
Minishell aims to replicate some basic functionalities of a Unix shell, allowing users to execute commands, manage processes, and perform basic file operations. It provides a minimalistic yet functional command-line interface for users to interact with their operating system.

## Features  
* Command Execution: Minishell executes commands inputted by users.
* Built-in Commands: Equipped with essential built-in commands like cd, echo, pwd, export, unset, env and exit.
* Signal Handling: Manages signals such as Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT) without unexpected termination.  
* Environment Variables: Facilitates management of environment variables through built-in commands such as export and unset, ensuring flexibility and customization.
* Redirection: Supports input and output redirection using <, >> and > symbols. Supports << heredoc redirection.
* Pipes: Implements command piping (|) functionality, enabling the sequential execution of commands where the output of one serves as input for another.

## Getting Started

1. Clone the repository:
   ```
   git clone https://github.com/dfneto/minishell.git
   ```
2. Navigate to the project directory:
   ```
   cd minishell
   ```
3. Compile the program:
   ```
   make
   ```

## Acknowledgments  
Minishell was developed as part of the curriculum at [42 Barcelona](https://www.42barcelona.com/).  
Thanks for the [mpanic](https://github.com/ChewyToast/mpanic) tests, these helped a lot the development of our project.
