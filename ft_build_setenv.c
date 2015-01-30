/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:01:16 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:01:18 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

#include <stdio.h>

static int	ft_correct_set_env(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (!(argv[i][0] && argv[i][0] != '='
			&& (ft_find_char(argv[i], '=') != -1)))
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

static int	ft_build_setenv_update(t_env *list, char *argv)
{
	int		index;

	index = ft_find_char(argv, '=');
	list->data = ft_strdup(ft_strsub(argv, index + 1, ft_strlen(argv) - index));
	return (1);
}

static void	ft_build_setenv_add(t_env *list, char *argv)
{
	int		index;

	index = ft_find_char(argv, '=');
	ft_envaddlast(&list, ft_envnew(ft_strsub(argv, 0, index),
		ft_strsub(argv, index + 1, ft_strlen(argv) - index)));
}

void		ft_build_setenv(t_env *list, char **argv)
{
	t_env	*tmp;
	int		i;
	int		find;

	i = 1;
	if (ft_correct_set_env(argv))
	{
		while (argv[i])
		{
			tmp = list;
			find = 0;
			while (tmp)
			{
				if (tmp->name && ft_strcmp(ft_strsub(argv[i], 0
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
