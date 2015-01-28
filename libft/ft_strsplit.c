/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/24 21:47:41 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

int		ft_height(char const *s, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			len++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (len);
}

char	*ft_extract_word(char const *s, char c)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_give_word(char const *s, int index, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && index == 0)
		{
			return (ft_extract_word(s + i, c));
		}
		index--;
		while (s[i] && s[i] != c)
			i++;
	}
	return (NULL);
}

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		height;
	char	**tab;

	i = 0;
	if (s && c)
	{
		height = ft_height(s, c);
		tab = (char **)malloc(sizeof(char *) * height);
		if (!tab)
			return (NULL);
		while (i < height - 1)
		{
			tab[i] = ft_give_word(s, i, c);
			i++;
		}
		tab[i] = 0;
		return (tab);
	}
	return (NULL);
}
