/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:48:57 by chtan             #+#    #+#             */
/*   Updated: 2024/09/06 20:08:26 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEMP_H
# define TEMP_H
# include "minishell.h"

typedef struct s_temp
{
	int		temp;
	char 	*temp_str;
	char 	**temp_split;
}				t_temp;

typedef struct s_key
{
	int key;
}		t_key;

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