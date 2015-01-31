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

#include <stdio.h>
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

static char	*ft_give_home(t_env **list)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->name && tmp->data && ft_strcmp(tmp->name, "HOME") == 0)
		{
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return ("");
}

static char	*ft_back_pwd(t_env **list)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->name && tmp->data && ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return ("");
}

void		ft_build_cd(char **argv, t_env **list)
{
	char	*path;
	char	buff[256];

	if (argv[1] == NULL)
		path = ft_strdup(ft_give_home(list));
	else if (ft_strcmp(argv[1], "-") == 0)
		path = ft_back_pwd(list);
	else
		path = ft_strdup(argv[1]);
	chdir(path);
	path = ft_strdup(getcwd(buff, 256));
	ft_fix_pwd(list, path);
}
