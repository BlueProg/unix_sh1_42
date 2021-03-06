/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:08:15 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:08:28 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	ft_print_env(t_env *list)
{
	t_env *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->name && tmp->data && (ft_strlen(tmp->name) > 0))
		{
			ft_putstr(tmp->name);
			ft_putstr("=");
			if (ft_strlen(tmp->data) > 0)
				ft_putendl(tmp->data);
			else
				ft_putendl("");
		}
		tmp = tmp->next;
	}
}

void	ft_build_env(t_env **list, char *cmd, char **argv)
{
	int	i;

	i = 1;
	if (ft_strcmp(cmd, "env") == 0)
		ft_print_env(*list);
	else if (ft_strcmp(cmd, "setenv") == 0)
		ft_build_setenv(*list, argv);
	else
	{
		while (argv[i])
		{
			ft_build_unsetenv(list, argv[i]);
			i++;
		}
	}
}
