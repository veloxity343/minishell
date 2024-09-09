/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:32:16 by chtan             #+#    #+#             */
/*   Updated: 2024/09/09 17:16:01 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
# include <_pid_t.h>

typedef struct s_temp // temp struct cause later on need to take from parsing
{
	int		temp;
	char 	*temp_str;
	char 	**temp_split;
}				t_temp;

typedef struct s_key
{
	int key;	//handle keycode and signal
}		t_key;

extern global_sig;

// utils
void	error_msg(char *msg);
void	undefined_message(char *command);
void	real_exit(void);


//exec
int		exec(char **array);

//pipex part
void	pipe_main(char **av, int ac, char **env);

//signal
void	ignore_signal(void);
void	exit_sig(int sig);

# endif
