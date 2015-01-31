/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:52:38 by mmole             #+#    #+#             */
/*   Updated: 2015/01/31 01:13:54 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH1_H
# define SH1_H

# include "libft/includes/libft.h"

typedef struct		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

void				ft_print_env(t_env *list);
void				ft_envaddlast(t_env **lst, t_env *add);
t_env				*ft_envnew(char const *name, char const *data);
void				ft_execute(char *path, char **argv);
void				ft_search_and_execute(char *cmd, t_env **list);
void				ft_build_setenv(t_env *list, char **argv);
void				ft_build_unsetenv(t_env **list, char **argv);
void				ft_build_env(t_env **list, char *cmd, char **argv);
void				ft_build_cd(char **argv, t_env **list);

#endif
