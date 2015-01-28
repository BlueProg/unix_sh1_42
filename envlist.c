/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 21:05:43 by mmole             #+#    #+#             */
/*   Updated: 2015/01/28 21:05:45 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h>
#include <string.h>

void	ft_envaddlast(t_env **lst, t_env *add)
{
	t_env	*tmp;

	tmp = *lst;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add;
	}
	else
		*lst = add;
}

t_env	*ft_envnew(char const *name, char const *data)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	if (!name || !data)
	{
		new_elem->name = NULL;
		new_elem->data = NULL;
	}
	else
	{
		new_elem->name = ft_strdup(name);
		new_elem->data = ft_strdup(data);		
		if (!new_elem->name || !new_elem->data)
			return (NULL);
	}
	new_elem->next = NULL;
	return (new_elem);
}
