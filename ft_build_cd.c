/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 18:38:05 by mmole             #+#    #+#             */
/*   Updated: 2015/01/31 01:09:39 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <unistd.h>

static void	ft_fix_pwd(t_env **list, char *path)
{
	t_env	*tmp;
	char	*expath;

	tmp = *list;
	while (tmp)
	{
		if (tmp->name && tmp->data && ft_strcmp(tmp->name, "PWD") == 0)
		{
			expath = ft_strdup(tmp->data);
			tmp->data = ft_strdup(path);
		}
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (tmp->name && tmp->data && ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			tmp->data = ft_strdup(expath);
			return ;
		}
		tmp = tmp->next;
	}
}

char		*ft_getenv(t_env **list, const char *name)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->name && tmp->data && ft_strcmp(tmp->name, name) == 0)
		{
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return ("");
}

static char *ft_tilde_path(t_env **list, char *argv)
{
	char *path;

	path = ft_getenv(list, "HOME");
	path = ft_strjoin(path, ft_strsub(argv, 1, ft_strlen(argv)));
	return (path);
}

static void ft_deplace(char *path, t_env **list)
{
	char	buff[256];

	chdir(path);
	if (access(path, F_OK) == -1)
		ft_putendl_fd("Path not exist", 2);
	else if (access(path, X_OK) == -1)
		ft_putendl_fd("Permission denied", 2);
	path = ft_strdup(getcwd(buff, 256));
	ft_fix_pwd(list, path);
}

void		ft_build_cd(char **argv, t_env **list)
{
	char	*path;

	if (argv[1] == NULL)
		path = ft_strdup(ft_getenv(list, "HOME"));
	else if (ft_strcmp(argv[1], "-") == 0)
		path = ft_getenv(list, "OLDPWD");
	else
	{
		if (argv[1][0] == '~')
			path = ft_tilde_path(list, argv[1]);
		else if (argv[1][0] == '/')
			path = ft_strdup(argv[1]);
		else
		{
			path = ft_strjoin(ft_getenv(list, "PWD"), "/");
			path = ft_strjoin(path, argv[1]);
		}
	}
	ft_deplace(path, list);
}
