/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/09/07 18:26:59 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/temp.h"
/*
	for the pipex part i need a struct contain of arguments,
	a struct contain of commands(token)
*/
void pipe_main(char **av, int ac, char **env)
{
	int pid;
	int fd[2];

	pid = fork();
	if (pid < 0|| pipe(fd == -1))
		error_msg("fork failed");
	//child
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		//parent
	}
	waitpid(pid, NULL, 0);
}