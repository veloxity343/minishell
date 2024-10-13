/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:17:45 by chtan             #+#    #+#             */
/*   Updated: 2024/10/13 11:38:28 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "minishell.h"
// # include <_pid_t.h>

# define R_END 0;
# define W_END 1;

//pipex
void	pipe_main(char **av, int ac, char **env);

#endif