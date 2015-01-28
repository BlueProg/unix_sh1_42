/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/22 15:48:54 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*strdst;
	const unsigned char	*strsrc;
	unsigned char		car;

	strdst = (unsigned char*)dst;
	strsrc = (const unsigned char*)src;
	car = (unsigned char)c;
	while (n--)
	{
		if ((*strdst++ = *strsrc++) == car)
			return (strdst);
	}
	return (NULL);
}
