/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:18:24 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/04 00:40:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printexport(void)
{
	while (g_gfl.env)
	{
		printf("declare -x %s=\"%s\"\n", g_gfl.env->name, g_gfl.env->value);
		g_gfl.env = g_gfl.env->next;
	}
	while (g_gfl.exp)
	{
		printf("declare -x %s\n", g_gfl.exp->name);
		g_gfl.exp = g_gfl.exp->next;
	}
}

char	**ft_export_spliter(char *str)
{
	int		i;
	char	**tab;
    char    *hold;

	i = 0;
    hold = str;
	tab = (char **)ft_calloc(3, sizeof(char *));
	if (!str || !*str)
	{
		free(tab);
		return (0);
	}
	tab[0] = (char *)ft_calloc((ft_dstrlen(str, '=') + 1), sizeof(char));
	while (str[i] != '=')
	{
		tab[0][i] = str[i];
		i++;
	}
	str = str + i + 1;
	tab[1] = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	i = 0;
	while (str[i])
	{
		tab[1][i] = str[i];
		i++;
	}
    free(hold);
	return (tab);
}

int	check_name(char *name, int opt)
{
	int i;

    i = 0;
    if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
        {
            if (i == ft_strlen(name) - 1 && opt == 1)
                return (1);
			return (0);
        }
        
		i++;;
	}
	return (1);
}

int	is_env(char **tab)
{
	t_env		*tmp;
	t_not_env	*tmp0;
	t_not_env	*holder2;
	t_export	*tmp1;
	t_export		*holder;
    

	tmp = g_gfl.env;
	tmp1 = g_gfl.exp;
	tmp0 = g_gfl.not_env;
	// case where name already in the env and need to be updated with the new val
	while (tmp)
	{
		if (!ft_strncmp(ft_strtrim(tab[0], "+"), tmp->name, 0))
		{
			
            if (tab[0][ft_strlen(tab[0]) - 1] == '+')
            {
                tab[1] = ft_strjoin(ft_strdup(tmp->value), tab[1]);
            }
            free(tmp->value);
			tmp->value = tab[1];
			free(tab[0]);
			return (1);
		}
		tmp = tmp->next;
	}
	//case where name is exported but has no value
    holder = 0;
    int i = 0;
	while (tmp1)
	{
        if (!ft_strncmp(ft_strtrim(tab[0], "+"), tmp1->name, 0))
		{
            tab[0] = ft_strtrim(tab[0], "+");
            if(!holder)
            {
                
                g_gfl.exp = tmp1->next;
                free(tmp1->name);
                free(tmp1);
                return (0);
            }
            else
            {
                holder->next = tmp1->next;
                free(tmp1->name);
                free(tmp1);            
			    return (0);
            }
		}
		holder = tmp1;
		tmp1 = tmp1->next;
        i++;
	}
	//case where name not a env val
	// while (tmp0)
	// {
	// 	if (!ft_strncmp(ft_strtrim(tab[0], "+"), tmp0->name,0))
	// 	{
	// 		holder2->next = tmp0->next;
	// 		freenode2(tmp0);
	// 		return (0);
	// 	}
	// 	holder2 = tmp0;
	// 	tmp0 = tmp0->next;
	// }
	return (0);
}

int	parss_export(char *str)
{
	int		i;
	char	**tab;

	if (ft_strchr(str, '='))
	{
		tab = ft_export_spliter(str);
		if (!check_name(tab[0], 1))
		{
			printf("export: `%s': not a valid identifier\n", tab[0]);
			ft_dfree(tab);
			return (1);
		}
		else if (!is_env(tab))
			ft_envadd_back(&g_gfl.env,ft_envnew(tab));
        free(tab);
	}
	else
	{
		if (check_name(str, 0))
			ft_exportadd_back(&g_gfl.exp, ft_exportnew(&str));
		else
        {
			printf("export: `%s': not a valid identifier\n", str);
            free(str);
        }
	}
	return (0);
}

void	export(char **str)
{
	int	optn;

	if (!str || !*str)
	{
		printexport();
		return ;
	}
	while (*str)
	{
		printf("[%p]",*str);
        parss_export(ft_strdup(*str));
		str++;
	}
}

int	main(int ac, char **av, char **env)
{
	if (!env || !*env)
		return (printf("no env\n"));

	t_env *head;
	char **arg;
	g_gfl.exp = 0;
	g_gfl.not_env = 0;
	arg = ft_split(env[0], '=');
	g_gfl.env = ft_envnew(arg);
	free(arg);
	head = g_gfl.env;
	env++;
	while (*env)
	{
		arg = ft_split(*env, '=');
		ft_envadd_back(&g_gfl.env, ft_envnew(arg));
		free(arg);
		env++;
	}
	g_gfl.env = head;
	export(av + 1);
	sleep(2);
	export(0);
	system("leaks exprt");
	return (0);
}