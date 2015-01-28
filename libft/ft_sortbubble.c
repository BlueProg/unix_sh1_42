/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortbubble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/22 15:42:57 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sortbubble(int **tab, size_t n)
{
	int		tmp;
	size_t	i;
	int		swap;

	swap = 1;
	while (swap == 1)
	{
		i = 1;
		swap = 0;
		while (i < (n))
		{
			if ((*tab)[i - 1] > (*tab)[i])
			{
				tmp = (*tab)[i - 1];
				(*tab)[i - 1] = (*tab)[i];
				(*tab)[i] = tmp;
				swap = 1;
			}
			i++;
		}
	}
}
