/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:15:47 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:46:07 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <unistd.h>
#include <dirent.h>

static char	**ft_parse_commande(char **cmd)
{
	char	**tab;
	int		i;

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

static char	*ft_find_path(char *cmd, char *path)
{
	char			**multipath;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	i = 0;
	multipath = ft_strsplit(path, ':');
	while (multipath[i])
	{
		dirp = opendir(multipath[i]);
		if (dirp == NULL)
			return (cmd);
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

void		ft_search_and_execute(char *cmd, t_env **list)
{
	char	**argv;
	char	*path;
	t_env	*tmp;

	tmp = *list;
	path = NULL;
	argv = ft_parse_commande(&cmd);
	if (tmp)
	{
		if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "setenv") == 0
			|| ft_strcmp(cmd, "unsetenv") == 0)
			ft_build_env(list, cmd, argv);
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
