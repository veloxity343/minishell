#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"

int		main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
	reset_fds(&mini);
	env_init(&mini, env);
	secret_env_init(&mini, env);
	increment_shell_level(mini.env);
	while (mini.exit == 0)
	{
		sig_init();
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	return (mini.ret);
}
