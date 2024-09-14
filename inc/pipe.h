/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:17:45 by chtan             #+#    #+#             */
/*   Updated: 2024/09/13 15:29:57 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "minishell.h"
# include <_pid_t.h>

//pipex
void	pipe_main(char **av, int ac, char **env);

#endif