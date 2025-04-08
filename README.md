# Minishell - 42 Project | Simple Bash Clone

## PROJECT DESCRIPTION
Implementation of a minimal Unix shell in C with basic command execution, pipes, redirections, and environment variable handling.

## TECHNICAL REQUIREMENTS
- Language: C (Norm compliant)
- Allowed functions: readline, fork, execve, pipe, dup2, etc.
- Memory: Zero leaks (except readline's known leaks)
- Signals: Handle ctrl-C/D/\
- Makefile: all, clean, fclean, re rules

## MANDATORY FEATURES
1. **Prompt**: Displays waiting symbol for new commands
2. **History**: Stores and navigates past commands
3. **Executables**: Finds programs via PATH or absolute paths
4. **Quoting**:
   - Single quotes: ignore all special chars
   - Double quotes: ignore most special chars except $
5. **Redirections**:
   - < (input)
   - > (output)
   - << (heredoc)
   - >> (append)
6. **Pipes**: | (multiple commands chained)
7. **Variables**:
   - Environment ($VAR)
   - Exit status ($?)
8. **Signals**:
   - ctrl-C: new prompt
   - ctrl-D: exit
   - ctrl-\: ignore
9. **Builtins**:
   - echo (-n option)
   - cd
   - pwd
   - export
   - unset
   - env
   - exit

## COMPILATION & USAGE
1. Build: `make`
2. Run: `./minishell`
3. Example commands:
   - `ls -la | grep .c > files.txt`
   - `echo $PATH`
   - `cd ~/projects && make`

## ERROR HANDLING
- Syntax errors (unclosed quotes, etc.)
- Command not found
- Permission denied
- Clean exit on errors

## NOTES
- Follows bash behavior for reference
- Single global variable allowed for signals
- Readline leaks are acceptable
- Must handle edge cases
