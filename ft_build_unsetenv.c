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

void	ft_build_unsetenv(t_env **list, char **argv)
{
	t_env	*currP;
	t_env	*prevP;
	int 	i;

	i = 0;
	prevP = NULL;
	currP = *list;
	while (argv[i])
		i++;
	while (i == 2 && currP != NULL)
	{
		if (ft_strcmp(currP->name,argv[1]) == 0)
		{
			if (prevP == NULL)
				*list = currP->next;
			else
				prevP->next = currP->next;
			free(currP);
			return;
		}
		prevP = currP;
		currP = currP->next;
	}
}
