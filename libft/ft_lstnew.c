/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/22 15:59:27 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	if (!content || content_size == 0)
	{
		new_elem->content = NULL;
		new_elem->content_size = 0;
	}
	else
	{
		new_elem->content = (void *)malloc(content_size);
		if (!new_elem->content)
			return (NULL);
		new_elem->content = ft_memcpy(new_elem->content, content, content_size);
		new_elem->content_size = (size_t)content_size;
	}
	new_elem->next = NULL;
	return (new_elem);
}
