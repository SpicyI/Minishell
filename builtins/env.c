/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:54:08 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/09 18:03:19 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(void)
{
	t_env	*env;

	env = g_gfl.env;
	while (env)
	{
		printf("%s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
