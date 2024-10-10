/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/10/10 10:40:55 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"
static void pipe_error(char *str)
{
	(void)str;
	ft_printf("pipe error\n");
	exit_sig(1);
}

/*
	for the pipex part i need a struct contain of arguments,
	a struct contain of commands(token)
*/
void	pipe_main(char **av, int ac, char **env)
{
	int i;
	int pid[];
	
	i = 0;
	
}

/*
char	*find_path(char *cmd_args, char **envp)
{
	char	**split_paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_paths = ft_split(envp[i], ':');
	i = 0;
	while (split_paths[i])
	{
		part_path = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(part_path, cmd_args);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (split_paths[++i])
		free(split_paths[i]);
	free(split_paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd_args;
	int		i;
	char	*split_path;

	i = -1;
	cmd_args = ft_split(argv, ' ');
	split_path = find_path(cmd_args[0], envp);
	if (!split_path)
	{
		while (cmd_args[++i])
			free(cmd_args[i]);
		free(cmd_args);
		error();
	}
	if (execve(split_path, cmd_args, envp) == -1)
		error();
}

int	gnl(char **line)
{
	char	*buffer;
	int		i;
	char	letter;

	i = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
	{
		*line = 0;
		return (-1);
	}
	read(0, &letter, 1);
	while (letter != '\n' && letter != '\0')
	{
		buffer[i++] = letter;
		read(0, &letter, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (1);
}

void	get_input(int *pipex, char **line, char *limiter)
{
	close(pipex[R_END]);
	write(1, "> ", 2);
	while (gnl(line))
	{
		if (ft_strncmp(*line, limiter, ft_strlen(limiter)) == 0)
			exit(EXIT_SUCCESS);
		write(1, "> ", 2);
		write(pipex[W_END], *line, ft_strlen(*line));
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	pid;
	int		pipex[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(pipex) == -1)
		error();
	pid = fork();
	if (pid == 0)
		get_input(pipex, &line, limiter);
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
	ft_printf("\033[0m");
	exit(EXIT_FAILURE);
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

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc < 5)
		usage();
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		i = 3;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		filein = open(argv[1], O_RDONLY, 0777);
		if (filein == -1)
			error();
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(filein, STDIN_FILENO);
	}
	while (i < argc - 2)
		child_n_parent(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}
*/