#ifndef BUILTIN_H
# define BUILTIN_H

# include "env.h"
# include <stdbool.h>

int			cd(char **args, t_entab *table);
void		add_pwd(t_entab *table);
void		update_oldpwd(char *oldpwd, t_entab *table);
void		update_pwd(char **args, t_entab *table);
int			echo(char **args);
int			print_env(char **args, t_entab *table);
int			exit_sh(char **arg, t_entab *table);
int			ft_export(char **args, t_entab *table);
int			pwd(char **args, t_entab *table);
int			unset(char **args, t_entab *table);

bool		ft_isbuiltin(const char *command);
int			run_builtin(const char **av, t_entab *table);

#endif