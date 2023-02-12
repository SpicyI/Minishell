/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:18:24 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/12 19:45:58 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printexport(void)
{
	t_env		*env;
	t_export	*exp;

	env = g_gfl.env;
	exp = g_gfl.exp;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	while (exp)
	{
		printf("declare -x %s\n", exp->name);
		exp = exp->next;
	}
}

char	**ft_export_spliter(char *str)
{
	char	**tab;
	char	*hold;

	hold = str;
	if (!str || !*str)
		return (0);
	tab = (char **)ft_calloc(3, sizeof(char *));
	tab[0] = ft_substr(str, 0, ft_dstrlen(str, '='));
	str = str + ft_dstrlen(str, '=') + 1;
	tab[1] = ft_strdup(str);
	free(hold);
	return (tab);
}

int	check_name(char *name, int opt)
{
	size_t	i;

	i = 0;
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if (name[i] == '+' && i == ft_strlen(name) - 1 && opt == 1)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	export_type(char **tab)
{
	if (is_env(tab))
		return (1);
	if (is_export(tab))
		return (0);
	if (is_not_env(tab))
		return (0);
	return (0);
}

int	export(char **str)
{
	int		sts;

	sts = 0;
	if (!str || !*str)
	{
		printexport();
		return (0);
	}
	while (*str)
	{
		if (ft_strchr(*str, '='))
			sts = exporter(ft_export_spliter(ft_strdup(*str)));
		else
			sts = importer(ft_strdup(*str));
		str++;
	}
	return (0);
}
