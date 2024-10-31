/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:28:12 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/31 13:42:12 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig		g_sig;

static void	ft_start_exec(t_mini *mini)
{
	signal(SIGQUIT, sig_quit);
	ft_init_tree(mini->ast, mini);
	if (g_sig.heredoc_sigint)
	{
		ft_clear_ast(mini, &mini->ast);
		g_sig.heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->ori_term);
	g_sig.exit_s = ft_exec_node(mini, false);
	ft_clear_ast(mini, &mini->ast);
}

static void	ft_init_mini(t_mini *mini, char **env)
{
	ft_memset(mini, 0, sizeof(t_mini));
	mini->env_var = env;
	ft_init_env(mini);
	mini->stdin = dup(0);
	mini->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &mini->ori_term);
	// initialize_shlvl(mini);
}

/*
@brief Processes a single line of input.
@param mini The minishell structure containing the current state.
@return None.
*/
static void	ft_process_input(t_mini *mini)
{
	mini->line = readline(PROMPT);
	if (!mini->line)
	{
		ft_clean_ms(mini);
		ft_putstr_fd("exit\n", 1);
		exit(g_sig.exit_s);
	}
	if (mini->line[0])
		add_history(mini->line);
	mini->tokens = ft_tokenize(mini);
	if (!mini->tokens)
		return ;
	mini->ast = ft_parser(mini);
	if (mini->parse_err.type)
		ft_handle_parse_err(mini);
	else
		ft_start_exec(mini);
}

/*
@brief Initializes the minishell and enters the main loop.
@param argc Argument count.
@param argv Argument vector.
@param env Environment variables.
@return Exit status.
*/
int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	((void)argc, (void)argv);
	ft_init_mini(&mini, env);
	while (1)
	{
		sig_init();
		ft_process_input(&mini);
	}
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(&mini), g_sig.exit_s);
}
