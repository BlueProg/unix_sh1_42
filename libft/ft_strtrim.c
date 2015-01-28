/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/19 17:12:47 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (s)
	{
		j = ft_strlen(s) - 1;
		str = (char *)malloc(sizeof(char) * ft_strlen(s));
		if (!str)
			return (NULL);
		while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i++;
		while (s[j] && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
			j--;
		while (i < j + 1)
			str[k++] = s[i++];
		str[k] = '\0';
		return (str);
	}
	return (NULL);
}
