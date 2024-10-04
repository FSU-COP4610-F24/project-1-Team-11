# Shell

[This project is designed to help us understand how the operating system works as far as communication with the shell environment. We needed to create the prompt, expand variables, work with paths, execute commands and child processes, implement io redirection, piping, and background processes.]

## Group Members
- **Donald Walton**: djw21c@fsu.edu
- **James Tanner**: jwt20@fsu.edu
- **Isabela Terra**: irt21@fsu.edu
## Division of Labor

### Part 1: Prompt
- **Responsibilities**: [Create a funtion that will print out the prompt]
- **Assigned to**: Donald Walton

### Part 2: Environment Variables
- **Responsibilities**: [Ceate a function that will expand the environment variables]
- **Assigned to**: Donald Walton


### Part 3: Tilde Expansion
- **Responsibilities**: [Create a tilde expression function that will help expand the tilde]
- **Assigned to**: Donald Walton, James Tanner

### Part 4: $PATH Search
- **Responsibilities**: [Create a function that will search certain commands if it exist or not]
- **Assigned to**: Donald Walton, Isabela Terra

### Part 5: External Command Execution
- **Responsibilities**: [Create a function that will process and output external commands and child processes.]
- **Assigned to**: Isabela Terra

### Part 6: I/O Redirectionhn
- **Responsibilities**: [Create a function that will implement IO redirection that will read/write/overwrite files]
- **Assigned to**: Donald Walton

### Part 7: Piping
- **Responsibilities**: [Create a funtion that will implement piping and all the aspects of piping.]
- **Assigned to**: James Tanner, Donald Walton

### Part 8: Background Processing
- **Responsibilities**: [Create a function that will implement background that is composed of both piping and IO redirection]
- **Assigned to**: Isabela Terra

### Part 9: Internal Command Execution
- **Responsibilities**: [Create a function that will help with internal commands such as jobs, cd, and exit]
- **Assigned**: Isabela Terra, James Tanner, Donald Walton


### Extra Credit
- **Responsibilities**: [Create a function that will help improve unlimited piping, suppot piping and io redirection on one single command line, and execute shell within a running shell]
- **Assigned to**: Donald Walton, James Tanner, Isabela Terra

## File Listing
```
shell/
│
├── src/
│ ├── lexer.c
│ 
│
├── include/
│ └── lexer.h
│
├── README.md
└── Makefile
```
## How to Compile & Execute

### Requirements
- **Compiler**: e.g., `gcc` for C/C++, `rustc` for Rust.
- **Dependencies**: List any libraries or frameworks necessary (rust only).

### Compilation
For a C/C++ example:
```bash
make
```
This will build the executable in ...
### Execution
```bash
make run
```
This will run the program ...

## Bugs
- **Bug 1**: This is bug 1.
- **Bug 2**: This is bug 2.
- **Bug 3**: This is bug 3.

## Extra Credit
- **Extra Credit 1**: [Extra Credit Option]
- **Extra Credit 2**: [Extra Credit Option]
- **Extra Credit 3**: [Extra Credit Option]

## Considerations
[Description]
