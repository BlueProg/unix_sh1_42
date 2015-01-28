/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/19 17:12:47 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	tmp = (char *)s1;
	if (!s2 || !*s2)
		return (tmp);
	if (s1)
	{
		while (s1[i])
		{
			j = 0;
			while (s1[i] != '\0' && s1[i] == s2[j])
			{
				i++;
				j++;
			}
			if (s2[j] == '\0')
				return (tmp + (i - ft_strlen(s2)));
			i = i - j;
			i++;
		}
	}
	return (NULL);
}
