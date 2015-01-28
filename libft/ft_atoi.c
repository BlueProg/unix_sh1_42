/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 17:12:46 by mmole             #+#    #+#             */
/*   Updated: 2015/01/22 15:42:40 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

int		ft_atoi(const char *str)
{
	size_t	i;
	int		number;
	int		total;
	int		negative;

	i = 0;
	number = 0;
	total = 0;
	negative = 1;
	while (str[i] && (str[i] == '\n' || str[i] == '\v' || str[i] == '\t' \
			|| str[i] == '\r' || str[i] == '\f' || str[i] == ' '))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (int)str[i] - 48;
		total = (total * 10) + number;
		i++;
	}
	return (total * negative);
}
