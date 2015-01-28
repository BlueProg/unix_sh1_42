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

// static void	print_env(t_env *list)
// {
// 	t_env *tmp;

// 	tmp = list;
// 	while (tmp)
// 	{
// 		if (tmp->name && tmp->data)
// 		{
// 			ft_putstr("name: ");
// 			ft_putendl(tmp->name);
// 			ft_putstr("data: ");
// 			ft_putendl(tmp->data);
// 		}
// 		tmp = tmp->next;
// 	}
// }

static void	ft_execute(char *path, char **argv)
{
	pid_t	father;

	if (*path)
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			return ;
		}
		if (father == 0)
		{
			execve(path, argv, NULL);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(path, 2);
			exit(1);
		}
	}
}

char 		**ft_parse_commande(char **commande)
{
	char 	**tab;

	tab = ft_strsplit(*commande, ' ');
	if (*tab)
	{
		*commande = ft_strdup(tab[0]);
		return (tab);
	}
	return (tab);
}

static char *ft_find_path(char *commande, char *path)
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
			return (commande);
		}
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_namlen == ft_strlen(commande)
				&& ft_strcmp(dp->d_name, commande) == 0)
			{
				(void)closedir(dirp);
				return (ft_strjoin(ft_strjoin(multipath[i], "/"), commande));
			}
		}
		(void)closedir(dirp);
		i++;
	}
	return (commande);
}

static void	ft_search_and_execute(char *commande, t_env *list)
{
	char **argv;
	char *path;
	t_env	*tmp;

	tmp = list;
	path = NULL;
	argv = ft_parse_commande(&commande);
	if (tmp)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, "PATH") == 0)
				path = ft_find_path(commande, tmp->data);
			tmp = tmp->next;
		}
	}
	ft_execute(path, argv);
}

static void	ft_read_input(char **commande)
{
	if (get_next_line(0, commande) < 0)
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
	char	*commande;
	t_env	*list;

	commande = NULL;
	list = NULL;
	ft_init_env(&list);
	//print_env(list);
	while (1)
	{
		ft_putstr("$> ");
		ft_read_input(&commande);
		if (ft_strcmp(commande, "exit") == 0)
			return (0);
		ft_search_and_execute(commande, list);
	}
	return (0);
}