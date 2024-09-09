/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/09/08 21:00:36 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/temp.h"
#include "../inc/define_lib.h"
extern int global_signal;
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
/*
	if (pid == 0)
	{
		close(pipex[R_END]);
		dup2(pipex[W_END], STDOUT_FILENO);
		close(pipex[W_END]);
		execute(argv, envp);
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipex[W_END]);
		dup2(pipex[R_END], STDIN_FILENO);
		close(pipex[R_END]);
	}v
*/