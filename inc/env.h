#ifndef ENV_H
# define ENV_H

# include <stdlib.h>

# ifndef SHELL
#  define SHELL "trash"
# endif

typedef struct s_envar
{
	char			*key;
	char			*val;
	int				state;
	char			*pwd;
	struct s_envar	*prev;
	struct s_envar	*next;
}	t_envar;

typedef struct s_entab
{
	int				size;
	t_envar			*head;
	t_envar			*tail;
}	t_entab;

#endif
