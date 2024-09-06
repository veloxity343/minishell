/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:46 by chtan             #+#    #+#             */
/*   Updated: 2024/09/06 19:45:55 by chtan            ###   ########.fr       */
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

	pid = fork();
	if (pid < 0)
		error_msg("fork failed");
	
}