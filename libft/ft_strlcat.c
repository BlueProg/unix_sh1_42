/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/19 17:12:47 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		nsv;
	size_t		buff;
	size_t		size2;

	nsv = size;
	size2 = ft_strlen(src);
	buff = ft_strlen(dst) + size2;
	while (*dst && size)
	{
		dst++;
		size--;
	}
	if (size == 0)
		return (nsv + size2);
	while (*src && size-- > 1)
		*dst++ = *src++;
	*dst = 0;
	return (buff);
}
