/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/19 17:12:47 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	j;
	char	*ret;

	i = 0;
	if (s && f)
	{
		j = ft_strlen(s);
		ret = (char *)malloc(sizeof(char) * ft_strlen(s));
		while (i < j)
		{
			ret[i] = (*f)(s[i]);
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
