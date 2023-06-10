# minishell-1

This is a project where you create your own shell in C. This project tries to replicate bash. The project has a few parts and was split between 2 people.
1) Parsing. The first part is reading the command line and storing everything in the appropriate manner to be executed. Parsing includes some error handling such as syntax errors, unclosed quotes, etc.
2) Execution. This is done after parsing has finished successfully without errors. Every command block must be executed in a child process, unless there is only one command block. Some error handling can be done in execution as well such as handling invalid commands, missing path to environment variables, etc.
3) Handling signals. This is a small part of the project, but still requires understanding of how signals work. Signals to be handled are Ctrl C, Ctrl D, and ignoring Ctrl "\".
