/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:52:38 by mmole             #+#    #+#             */
/*   Updated: 2015/01/28 16:52:43 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h> // exit
#include <unistd.h> // execve
#include <dirent.h> // opendir readdir closedir DIR

/*
	access check si path est valide ou droit ok.

	voir signal.
*/

#include <stdio.h>

static void	ft_print_env(t_env *list)
{
	t_env *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->name && tmp->data && (ft_strlen(tmp->name) > 0) && (ft_strlen(tmp->data) > 0))
		{
			ft_putstr(tmp->name);
			ft_putstr("=");
			ft_putendl(tmp->data);
		}
		tmp = tmp->next;
	}
}

int 		ft_only_space(char *path)
{
	int i;
	int find;

	i = 0;
	find = 0;
	while (path[i])
	{
		if (path[i] != ' ')
			find = 1;
		i++;
	}
	if (find == 1)
		return (1);
	return (0);
}

static void	ft_execute(char *path, char **argv)
{
	pid_t		father;
	extern char **environ;


	if (path && *path && ft_only_space(path))
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			return ;
		}
		if (father == 0)
		{
			execve(path, argv, environ);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(path, 2);
			exit(1);
		}
	}
}

char 		**ft_parse_commande(char **cmd)
{

	char 	**tab;
	int 	i;

	i = 0;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '\t')
			(*cmd)[i] = ' ';
		i++;
	}
	tab = ft_strsplit(*cmd, ' ');
	if (*tab)
	{
		*cmd = ft_strdup(tab[0]);
		return (tab);
	}
	return (tab);
}

static char *ft_find_path(char *cmd, char *path)
{
	char 			**multipath;
	DIR 			*dirp;
	struct dirent	*dp;
	int 			i;

	i = 0;
	multipath = ft_strsplit(path, ':');
	while (multipath[i])
	{
		dirp = opendir(multipath[i]);
		if (dirp == NULL)
		{
			return (cmd);
		}
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_namlen == ft_strlen(cmd)
				&& ft_strcmp(dp->d_name, cmd) == 0)
			{
				(void)closedir(dirp);
				return (ft_strjoin(ft_strjoin(multipath[i], "/"), cmd));
			}
		}
		(void)closedir(dirp);
		i++;
	}
	return (cmd);
}

/*
	Ajout un nouvelle element dans lenvironnement.
	Si lelement existe deja, il le modifie sinon, il le cree.
*/

int 		ft_correct_set_env(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (!(argv[i][0] && argv[i][0] != '=' && (ft_find_char(argv[i], '=') != -1)))
		{
			ft_putendl_fd("Bad setenv", 2);
			return (0);
		}
		i++;
	}
	if (i != 1)
		return (1);
	ft_putendl_fd("Bad setenv", 2);
	return (0);
}

int 		ft_build_setenv_update(t_env *list, char *argv)
{
	int 	index;

	index = ft_find_char(argv, '=');
	list->data = ft_strdup(ft_strsub(argv, index + 1, ft_strlen(argv) - index));
	return (1);
}

void		ft_build_setenv_add(t_env *list, char *argv)
{
	int 	index;

	index = ft_find_char(argv, '=');
	ft_envaddlast(&list, ft_envnew(ft_strsub(argv, 0, index),
		ft_strsub(argv, index + 1, ft_strlen(argv) - index)));
}

void		ft_build_setenv(t_env *list, char **argv)
{
	t_env	*tmp;
	int 	i;
	int 	find;

	i = 1;
	if (ft_correct_set_env(argv))
	{
		while (argv[i])
		{
			tmp = list;
			find = 0;
			while (tmp)
			{
				if (ft_strcmp(ft_strsub(argv[i], 0
					, ft_find_char(argv[i], '=')), tmp->name) == 0)
					find = ft_build_setenv_update(tmp, argv[i]);
				tmp = tmp->next;
			}
			if (find == 0)
				ft_build_setenv_add(list, argv[i]);
			i++;
		}
	}
}

void		ft_build_unsetenv(t_env *list, char **argv)
{
	int i;
	t_env 	*tmp;
	t_env 	*pred;

	tmp = list;
	pred = tmp;
	i = 0;
	while (argv[i])
		i++;
	if (i == 2)
	{
		while (tmp)
		{

			if (ft_strcmp(tmp->name, argv[1]) == 0)
			{
				pred->next = tmp->next;
				free(tmp->name);
				free(tmp->data);
				tmp->name = NULL;
				tmp->data = NULL;
				free(tmp);
				tmp = pred;
				return ;
			}
			pred = tmp;
			tmp = tmp->next;
		}
	}
}

void		ft_build_env(t_env *list, char *cmd, char **argv)
{
	if (ft_strcmp(cmd, "env") == 0)
		ft_print_env(list);
	else if (ft_strcmp(cmd, "setenv") == 0)
		ft_build_setenv(list, argv);
	else
		ft_build_unsetenv(list, argv);
}

static void	ft_search_and_execute(char *cmd, t_env *list)
{
	char **argv;
	char *path;
	t_env	*tmp;

	tmp = list;
	path = NULL;
	argv = ft_parse_commande(&cmd);
	if (tmp)
	{
		if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "setenv") == 0
			|| ft_strcmp(cmd, "unsetenv") == 0)
			ft_build_env(tmp, cmd, argv);
		// else if (ft_strcmp(cmd, "cd") == 0)
		// 	ft_build_cd(cmd, argv);
		else
		{
			while (tmp)
			{
				if (tmp && tmp->name && (ft_strcmp(tmp->name, "PATH") == 0))
					path = ft_find_path(cmd, tmp->data);
				tmp = tmp->next;
			}
			ft_execute(path, argv);
		}
	}
}

static void	ft_read_input(char **cmd)
{
	if (get_next_line(0, cmd) < 0)
	{
		ft_putendl_fd("Error read", 2);
		exit(-1);
	}
}

static void	ft_init_env(t_env **list)
{
	extern char **environ;
	int 		i;
	int 		index;

	i = 0;
	index = -1;
	if (environ && *environ)
	{
		while (environ[i])
		{
			if ((index = ft_find_char(environ[i], '=')) != -1)
			{
				ft_envaddlast(list, ft_envnew(ft_strsub(environ[i]
					, 0, index), ft_strsub(environ[i], index + 1
					, ft_strlen(environ[i]) - index)));
			}
			i++;
		}
	}
	else
		ft_envaddlast(list, ft_envnew(NULL, 0));
}

int			main()
{
	char	*cmd;
	t_env	*list;

	cmd = NULL;
	list = NULL;
	ft_init_env(&list);
	while (1)
	{
		ft_putstr("$> ");
		ft_read_input(&cmd);
		// printf("read\n");
		if (ft_strcmp(cmd, "exit") == 0)
			return (0);
		ft_search_and_execute(cmd, list);
	}
	return (0);
}
