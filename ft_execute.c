/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:12:33 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:47:08 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h>
#include <unistd.h>

static int		ft_only_space(char *path)
{
	int	i;
	int	find;

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

static char		**ft_create_environ(t_env **list, int i)
{
	t_env	*tmp;
	char	**tab;

	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = *list;
	if ((tab = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	i = -1;
	while (tmp && ++i > -1)
	{
		if (tmp->name && tmp->data)
		{
			tab[i] = ft_strjoin(ft_strdup(tmp->name), "=");
			tab[i] = ft_strjoin(tab[i], ft_strdup(tmp->data));
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void			ft_execute(char *path, char **argv, t_env **list)
{
	pid_t		father;
	int			i;

	i = 0;
	if (path == NULL)
		ft_putendl_fd("Command not found", 2);
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
			execve(path, argv, ft_create_environ(list, i));
			ft_putstr_fd("Command not found: ", 2);
			ft_putendl_fd(path, 2);
			exit(1);
		}
	}
}
