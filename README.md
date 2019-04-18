# codam-42sh [![Build Status](https://travis-ci.com/OscarMulder/codam-42sh.svg?token=npJorzrMuT9oxn5xXSyd&branch=master)](https://travis-ci.com/OscarMulder/codam-42sh) [![codecov](https://codecov.io/gh/OscarMulder/codam-42sh/branch/master/graph/badge.svg?token=hg6wEBSVIc)](https://codecov.io/gh/OscarMulder/codam-42sh)

## Definitions of functions
Functions names should start with the shell-category they belong to.
- General shell related -> shell_
- Terminal configuaration -> term_
- Input converter -> input_
- Parser -> parser_
- Executor -> exec_
- Builtins -> builtin_
- Libft -> ft_
- Tests -> test_

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

## Adding tests

1. Create a new file in test/ called test_NAME_OF_FUNCTION.c
2. Add function prototype to test.h header
3. Add test to test_main.c
4. Add name of testfile to "TESTS" variable in Makefile
5. Test if the test passes with 'make test'
6. Travis wil automatically run the test on push.

## Github workflow
Because we want to make sure we have a good experience working on this project together, we setup a more advanced github workflow. Please keep the following things in mind while pushing to github.
- Every feature has it's own branch, which will be merged via a push request on Github.
- You NEVER push directly to master (exception for updating the README.md)
- The master branch should always pass the build/tests. It should be the stable version.
- While working on a branch, start your push request with "WIP" (work in progress). This will prevent the build from becoming "green". Which means it's not allowed to merge it to master. When you are ready to merge, remove WIP from the push request title.
- We want to test as much of the code as possible, so make sure to write tests for the code you commit.
- Please have someone (or everyone) look at your code before merging to master. Just because we can all merge doesn't mean we should.
- After succesfully merging a branch, delete it (after pressing the merge button, a delete button will appear).
- Travis will run a lot! Please wait for it to finish before merging to master.
- Commit messages have to be in English, they should also make sense. Especially while merging.