/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/10/14 15:15:31 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int global_signal;

// static void use_case() {
// 	ft_dprintf(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n");
// 	exit_sig(1);
// }

/*
	for the pipex part i need a struct contain of arguments,
	a struct contain of commands(token)

	f1)checking argument but not suitable to use in this case
	but the usage is not useful this time cause
	we didn't pass arguments to pipe

	f2) also won't just directly check here doc. should change
*/
int	main(int ac, char **av, char **env)
{
	int filein;
	int fileout;
	int i;

	if (ac < 5)//f1
		usage();
	if (ft_strncmp(av[1], "here_doc", 9) == 0) //f2
	{
		i = 3;
		fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		filein = open(av[1], O_RDONLY, 0777);
		if (filein == -1)
			error();
		fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(filein, STDIN_FILENO);
	}
	while (i < ac - 2)
		child_n_parent(av[i++], env);
	dup2(fileout, STDOUT_FILENO);
	execute(av[ac - 2], env);
}

void	child_n_parent(char *argv, char **envp)
{
	pid_t	pid;
	int		pipex[2];

	if (pipe(pipex) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
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
	}
}

void	usage(void)
{
	ft_putstr_fd("\033[31mError: \033[33mInproper Arguments\n\033[0m", 2);
	ft_putstr_fd(
		"\033[33mEx: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n\033[0m", 1);
	exit(EXIT_SUCCESS);
}

void	error(void)
{
	perror("\033[31mError");
	printf("\033[0m");
	exit(EXIT_FAILURE);
}
