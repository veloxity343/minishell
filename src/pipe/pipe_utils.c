/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:55:02 by kytan             #+#    #+#             */
/*   Updated: 2024/10/13 11:46:10 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipe.h"

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
