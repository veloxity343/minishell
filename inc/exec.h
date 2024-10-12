/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:32:16 by chtan             #+#    #+#             */
/*   Updated: 2024/10/12 18:46:57 by rcheong          ###   ########.fr       */
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

//signal
void	ignore_signal(int sig);
void	exit_sig(int sig);

# endif
