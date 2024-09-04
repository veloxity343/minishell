# <p align='center'>Welcome to our T.R.A.S.H. minishell!</p>

If you're wondering why we named our shell so atrociously, <i>trash</i> is an acronym for The Really Absurd Shell. So you see, we're a pretty funny pair...

### Logs
1. - [x] Makefile written
2. - [x] libft added
3. - [x] Roles assigned: 
	<ul>
		<li>Ryan parsing</li>
		<li>Jaxz executing</li>
	</ul>
4. - [ ] Parsing:
		- [x] Wrote skeleton main function
  		- [ ] Tokenizing inputs and lexical analysis
		- [ ] Determine and apply grammar
		- [ ] Build a parse tree in order of token precedence
5. - [ ] Executing:
         	<ol>
	  	</ol>
6. - [ ] Testing
7. - [ ] Final norme check

### Features
Formula for shell fundamentals: <code>lexer</code> -> <code>parser</code> -> <code>expander</code> -> <code>executor</code>
<ol>
	<li>Main program: continuously prompts user for input, reads input, waits for the next cmd
		<ul>
			<li>Customisable shell prompt: trash</li>
			<li>readline to capture user input</li>
		</ul>
	</li>
	<li>Parsing user input:
		<ul>
			<li>Tokenization to breakdown user input into cmds and args; handle special chars like <code>|, >, <, ;</code></li>
			<li>Handle quoting or escaping</li>
			<li>Expand env vars: replace vars like <code>$PATH</code> with values from env</li>
		</ul>
	</li>
</ol>
