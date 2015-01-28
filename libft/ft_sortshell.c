/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/22 15:42:57 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sortshell(int **tab, size_t n)
{
	int		tmp;
	size_t	pas;
	size_t	i;
	size_t	j;

	pas = 0;
	while (pas < n)
		pas = 3 * pas + 1;
	while (pas > 0)
	{
		pas = pas / 3;
		i = 0;
		while (i < n)
		{
			j = i;
			tmp = (*tab)[i];
			while ((j >= pas) && ((*tab)[j - pas] > tmp))
			{
				(*tab)[j] = (*tab)[j - pas];
				j = j - pas;
			}
			(*tab)[j] = tmp;
			i++;
		}
	}
}
