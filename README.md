# codam-42sh [![codecov](https://codecov.io/gh/OscarMulder/codam-42sh/branch/master/graph/badge.svg?token=hg6wEBSVIc)](https://codecov.io/gh/OscarMulder/codam-42sh)

## Pillars of VSH
1. Test EVERYTHING.
2. Write clear and concise comments above functions that need it.
3. Only allocate heap memory when it makes sense. (i.e. don't allocate or copy a string when you don't need to change it ever)
4. Keep your functions short & sweet. Make sure they really do only one thing. This makes them easier to test as well.
5. Stability, if you know your code isn't good enough yet, please add a comment so others know as well. Consider not merging it to master yet.
6. Communicate all the things! The slack chat is a safe space, feel free and safe to express your feelings if you are annoyed, scared, confused or otherwise emotionally unstable.

## Structure of the shell
We will structure the shell based on `Bash: 3.1.1 Shell Operation`

The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status (see Exit Status).

## Adding tests

1. Create a new file in `test/` called `test_`*NAME_OF_FUNCTION*`.c`.
2. Add function prototype to `test.h` header.
3. Add test to `test_main.c`.
4. Add name of testfile to "`TESTS`" variable in Makefile.
5. Test if the test passes with '`make test`'.
6. Travis wil automatically run the test on push.

## Github workflow
Because we want to make sure we have a good experience working on this project together, we setup a more advanced github workflow. Please keep the following things in mind while pushing to github.
- Every feature has it's own branch, which will be merged via a push request on Github.
- You NEVER push directly to master (exception for updating the README.md).
- The master branch should always pass the build/tests. It should be the stable version.
- While working on a branch, start your push request with "WIP" (work in progress). This will prevent the build from becoming "green", which means it's not allowed to merge it to master. When you are ready to merge, remove WIP from the push request title.
- We want to test as much of the code as possible, so make sure to write tests for the code you commit.
- Have atleast 2 team members review your code before merging to master.
- After succesfully merging a branch, delete it (after pressing the merge button, a delete button will appear).
- Travis will run a lot! Please wait for it to finish before merging to master.
- Commit messages have to be in English, they should also make sense. Especially while merging.
- Trigger github action

Naming conventions
===
KEEP IN MIND: Code is written to be understood by humans, not by computers.<br />
KEEP IN MIND: Long, descriptive variable names **can** be useful, but you don't always need them.
## Naming: branches
- Branch names should be clear and concise
## Naming: files
- `.c` files should have the same name as the most important function they contain.
## Naming: functions
Functions names should start with the category that they belong to.
- General shell related -> `shell_`
- Terminal configuaration -> `term_`
- Input converter -> `input_`
- Parser -> `parser_`
- Executor -> `exec_`
- Builtins -> `builtin_`
- Libft -> `ft_`
- Tests -> `test_`
## Naming: functions, variables and defines
1. Names should be as concise as possible whilst still being readable. Don't use weird abbreviations.
  - Example: name functions `parser_replace_wildcards`, **instead of** `prsr_rep_wldcrds**`.
  - If a variable is used as an iterator or index in a loop and doesn't hold any other important meaning, it shall be named i, j or k.<br/>(If you need a 'k' please consider refactoring your code.)
2. Names should make sense and give a clear indication of their purpose when needed.
  - Example: name functions `parser_replace_wildcards` **instead of** `parser_wildcards`.
  - Example: name variables `int total_words` and `int total_chars` **instead of** `int counter1` and `int counter2`.
3. Defines should start with the function name they belong to. L (lowercase) and U (uppercase) are used to specifiy if an option/flag is upper or lowercase.
  - Example: name define `ECHO_HOME` **instead of** `HOME`.
  - Example: name option/flag `ECHO_OPT_EU` and `ECHO_OPT_EL` **instead of** `ECHO_OPT_CE` or `ECHO_OPT_E`.

## Running in Docker
First, build the container:
```
docker build -t vsh .
```
Then, run the container from the repository dir:
```
docker run -v $PWD:/vsh -it vsh
```
To run the tests you can type `make test` or `make test_valgrind` to run the tests with valgrind.
Usefull commands:
```
docker ps	#lists running containers
docker images	#lists docker images on system
```
