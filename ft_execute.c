/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 22:12:33 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:47:08 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h>
#include <unistd.h>

static int		ft_only_space(char *path)
{
	int	i;
	int	find;

	i = 0;
	find = 0;
	while (path[i])
	{
		if (path[i] != ' ')
			find = 1;
		i++;
	}
	if (find == 1)
		return (1);
	return (0);
}

void			ft_execute(char *path, char **argv)
{
	pid_t		father;
	extern char	**environ;

	if (path && *path && ft_only_space(path))
	{
		father = fork();
		if (father > 0)
		{
			wait(NULL);
			return ;
		}
		if (father == 0)
		{
			execve(path, argv, environ);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(path, 2);
			exit(1);
		}
	}
}
