/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:48:57 by chtan             #+#    #+#             */
/*   Updated: 2024/09/06 14:50:32 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEMP_H
# define TEMP_H
# include "minishell.h"

typedef struct s_temp
{
	int		temp;
	char 	*temp_str;
	char 	**temp_split;
}				t_temp;

typedef struct s_key
{
	int key;
}		t_key;

# endif