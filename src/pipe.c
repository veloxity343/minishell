/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/09/09 15:06:00 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"
extern int global_signal;
/*
	for the pipex part i need a struct contain of arguments,
	a struct contain of commands(token)
*/
void pipe_main(char **av, int ac, char **env)
{
	pid_t pid;
	int fd[2];

	pid = fork();
	if (pid < 0|| pipe(fd == -1)) // error handling cause -1 of fork is error and also pipe
		error_msg("fork failed");
	if (pid == 0) //child process
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else //parent process
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
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