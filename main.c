/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:52:38 by mmole             #+#    #+#             */
/*   Updated: 2015/01/29 22:49:07 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdlib.h>
#include <signal.h>

static void	ft_read_input(char **cmd)
{
	int		ret;

	if ((ret = get_next_line(0, cmd)) < 0)
	{
		ft_putendl_fd("Error read", 2);
		exit(-1);
	}
	else if (ret == 0)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}

static void	ft_init_env(t_env **list)
{
	extern char	**environ;
	int			i;
	int			index;

	i = 0;
	index = -1;
	if (environ && *environ)
	{
		while (environ[i])
		{
			if ((index = ft_find_char(environ[i], '=')) != -1)
			{
				ft_envaddlast(list, ft_envnew(ft_strsub(environ[i]
					, 0, index), ft_strsub(environ[i], index + 1
					, ft_strlen(environ[i]) - index)));
			}
			i++;
		}
	}
	else
		ft_envaddlast(list, ft_envnew(NULL, 0));
}

int			main(void)
{
	char	*cmd;
	t_env	*list;
	char	**multi;

	cmd = NULL;
	list = NULL;
	ft_init_env(&list);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		ft_putstr("\033[33m");
		ft_putstr(ft_getenv(&list, "PWD"));
		ft_putstr(": ");
		ft_putstr("\033[0m");
		ft_read_input(&cmd);
		if (ft_strcmp(cmd, "exit") == 0)
			return (0);
		multi = ft_strsplit(cmd, ';');
		while (*multi)
		{
			ft_search_and_execute(*multi, &list);
			multi++;
		}
	}
	return (0);
}
