# <p align='center'>Welcome to our T.R.A.S.H. minishell!</p>

If you're wondering why we named our shell so atrociously, <i>trash</i> is an acronym for The Really Absurd Shell. So you see, we're a pretty funny pair...

## Logs:

1. Makefile written ✅
2. libft added ✅
3. Roles:
	a. Ryan parsing
	b. Jaxz executing
4. Formula for shell fundamentals lexer -> parser -> expander -> executor
	a. Main program: continuously prompts user for input, reads input, waits for the next cmd
		i. Customisable shell prompt: trash
		ii. readline to capture user input
	b. Parsing user input:
		i. Tokenisation to breakdown user input into cmds and args; handle special chars like |, >, <, ;
		ii. Handle quoting or escaping
		iii. Expand env vars: replace vars like $PATH with values from env
	