/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:32:16 by chtan             #+#    #+#             */
/*   Updated: 2024/10/18 11:31:25 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
// # include <_pid_t.h>

typedef struct s_temp // temp struct cause later on need to take from parsing
{
	int		temp;
	char 	*temp_str;
	char 	**temp_split;
}				t_temp;

typedef struct s_system
{
	int std_flag;
	int shell_lv;
}	t_system;

extern int global_sig;

// utils
void	error_msg(char *msg);
void	undefined_message(char *command);
void	real_exit(void);


//exec
int		exec(char **array, char **envp);
int		ft_exec(t_token *token);

//signal
void	ignore_signal(int sig);
void	exit_sig(int sig);

# endif
