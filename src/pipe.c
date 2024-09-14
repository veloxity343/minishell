/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/09/14 15:51:17 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"
int global_signal;
static void use_case() {
	ft_dprintf(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n");
	exit_sig(1);
}

/*
	for the pipex part i need a struct contain of arguments,
	a struct contain of commands(token)
*/
void	pipe_main(char **av, int ac, char **env)
{
	int filein;
	int fileout;
	int i;

	if (ac < 5)
		use_case();
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
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
			error_msg("File not found");
		fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(filein, STDIN_FILENO);
	}
	
}
