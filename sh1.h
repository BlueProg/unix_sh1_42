/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:52:38 by mmole             #+#    #+#             */
/*   Updated: 2015/01/28 16:52:43 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SH1_H
# define SH1_H

#include "libft/includes/libft.h"

typedef struct 		s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}					t_env;

void				ft_envaddlast(t_env **lst, t_env *add);
t_env				*ft_envnew(char const *name, char const *data);

#endif