/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:17:45 by chtan             #+#    #+#             */
/*   Updated: 2024/10/13 11:51:19 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "minishell.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include "../libft/inc/ft_dprintf.h"
// # include <_pid_t.h>
    
# define R_END 0
# define W_END 1

//pipex
void	pipe_main(char **av, int ac, char **env);
void	child_n_parent(char *argv, char **envp);

//utils
char    *find_path(char *cmd_args, char **envp);
void    execute(char *argv, char **envp);
int     gnl(char **line);
void	get_input(int *pipex, char **line, char *limiter);
void	here_doc(char *limiter, int argc);

#endif