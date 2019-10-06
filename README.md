## What is VelaSHell
Velashell (<B>vsh</B>) is a bash-styled shell school project completely written
from scratch in C with very limited access to libraries and tools. We worked on
it with 5 people for a total duration of around 5 months.

## The (learning) goals of the project:
- To complete the final project in our school's pre-internship UNIX branch.
- Learn a lot more about the inner workings of the UNIX system.
- Learn about all the different type of shell implementations.
- Learn how to write our own lexer from scratch in C (**no tools allowed**).
- Learn how to write our own parser from scratch in C
  (**again, no tools allowed**).
- Learn how to write nice and clean code.
- To create a stable and complete UNIX shell.

## Installing and running VelaSHell
Install:
```
make && make clean
```

Run:
```
./vsh
```

## Project General Instructions
1. The shell can not leak in any way.
2. In no way can the shell quit in an unexpected manner (e.g. segfault).
3. We may only use the following `libc` functions, anything else is
   **prohibited**:
   1. the whole `man 2` section
   2. `malloc`, `free`, `opendir`, `readdir`, `opendir`, `getcwd`, `signal`,
      `exit`, `isatty`, `ttyname`, `ttyslot`, `getenv`, `tcsetattr`,
      `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto` and
      `tputs`.
   3. `termcaps`
   4. Instead of the standard `libc` library, we use our own library functions
      (like `ft_printf` instead of `printf`). We made all these functions in
      earlier projects at our school (you can check them out at `srcs/libft`).
4. The terminal must be clean and not display gibberish.

## Functionality
1. Error monitoring without using `errno`
2. Prompt display
3. Complete management of input
4. Handle terminal resizing
5. (Multiline) line edition
6. Redirection with the following operators:
   1. `>`
   2. `>>`
   3. `<`
   4. `<<`
   5. `>&`
   6. `<&`
7. Control operators:
   1. `|`
   2. `||`
   3. `&`
   4. `&&`
   5. `;`
8. Pipelines
9. Internal shell variable monitoring
10. Job control monitoring (WIP)
11. Globing (WIP)
12. Signal monitoring
13. Quoting through `"`, `'`, and `\`
14. Basic parameter expansion
15. Complete management of command history (WIP)
16. Alias management
17. Hash table
18. Autocomplete
19. Builtins:
    1.  `echo`
    2.  `cd`
    3.  `fc`
    4.  `env`
    5.  `set`
    6.  `unset`
    7.  `exit`
    8.  `export`
    9.  `history`
    10. `alias`
    11. `unalias`
    12. `type`
    13. `hash`
20. A manual page called `vsh.1`

## Reading the manual
The VSH manual contains a thorough description of our shell.
\
Run:
```
man ./vsh.1
```

## Github workflow
Because we want to make sure we have a good experience working on this project together, we setup a more advanced github workflow. Please keep the following things in mind while pushing to github.
- Every feature has its own branch, which will be merged via a pull request on Github.
- The master branch is the stable version.
- We want to test as much of the code as possible, so make sure to write tests for the code you commit.
- Have atleast 2 team members review your code before merging to master.
- Commit messages have to be in English, they should also make sense. Especially while merging.

## Authors
[Jorn Brinksma](https://github.com/jbrinksma),
[Marijn van Heesewijk](https://github.com/marijnvanh),
[Oscar Mulder](https://github.com/OscarMulder),
[Rob Kuijper](https://github.com/robkuijper),
[Thijs de Jong](https://github.com/thijsdejong)