/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortquick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/22 15:42:57 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swapquick(int **tab, const int i, const int j)
{
	int	tmp;

	tmp = (*tab)[i];
	(*tab)[i] = (*tab)[j];
	(*tab)[j] = tmp;
}

int		partition(int **tab, const int start, const int end)
{
	int	compteur;
	int	pivot;
	int	i;

	compteur = start;
	pivot = (*tab)[start];
	i = start + 1;
	while (i <= end)
	{
		if ((*tab)[i] < pivot)
		{
			compteur++;
			swapquick(tab, compteur, i);
		}
		i++;
	}
	swapquick(tab, compteur, start);
	return (compteur);
}

void	sortquickaux(int **tab, const int start, const int end)
{
	int	pivot;

	if (start < end)
	{
		pivot = partition(tab, start, end);
		sortquickaux(tab, start, pivot - 1);
		sortquickaux(tab, pivot + 1, end);
	}
}

void	ft_sortquick(int **tab, size_t n)
{
	sortquickaux(tab, 0, n - 1);
}
