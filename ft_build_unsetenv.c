/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_unsetenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:01:33 by mmole             #+#    #+#             */
/*   Updated: 2015/01/31 01:14:27 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h>

void	ft_build_unsetenv(t_env **list, char **argv)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 0;
	curr = *list;
	while (argv[i])
		i++;
	while (i == 2 && curr != NULL)
	{
		if (curr->name && ft_strcmp(curr->name, argv[1]) == 0)
		{
			if (prev == NULL)
				*list = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
