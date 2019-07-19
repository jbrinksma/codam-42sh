# To do:

- Wildcard expansions (ast compatible) (will need to expand one command, wait for it to finish, and then expand the next one etc.)
- Builtin job manager (taskmaster)
- Pipe/redirect handling
- Allow processes to run in background
- Fix parse tree ASSIGN items in prefix (seems to only keep the last assignment or redirect in prefix of command)
- Fix parse tree printer

## Executor
- Connect to wildcard expansion function
- Implement redirections between commands
- Connect to taskmanager
- Connect to function that allows for background processes