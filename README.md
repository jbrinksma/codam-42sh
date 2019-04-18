# codam-42sh [![Build Status](https://travis-ci.com/OscarMulder/codam-42sh.svg?token=npJorzrMuT9oxn5xXSyd&branch=master)](https://travis-ci.com/OscarMulder/codam-42sh)

## Definitions of functions
Functions names should start with the shell-category they belong to.
- General shell related -> shell_
- Terminal configuaration -> term_
- Input converter -> input_
- Parser -> parser_
- Executor -> exec_
- Builtins -> builtin_
- Libft -> ft_

## Structure of the shell
We will structure the shell based on Bash: 3.1.1 Shell Operation

The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status (see Exit Status). 
