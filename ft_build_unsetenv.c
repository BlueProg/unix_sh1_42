/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_unsetenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:01:33 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:01:34 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h>

void	ft_build_unsetenv(t_env *list, char **argv)
{
	int		i;
	t_env	*tmp;
	t_env	*pred;

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
