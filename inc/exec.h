/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:32:16 by chtan             #+#    #+#             */
/*   Updated: 2024/09/09 13:32:29 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

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

int global_sig = 0;

// utils
void	error_msg(char *msg);

//exec
int exec(char **array);

//pipex part
void pipe_main(char **av, int ac, char **env);

//signal
void	ignore_signal(void);
void	exit_sig(int sig);

# endif