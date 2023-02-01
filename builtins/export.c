/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:18:24 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/01 23:23:10 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envnew(char **content)
{
	t_env	*new_node;

	new_node = (t_env *) malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->name = content[0];
    new_node->value = content[1];
	new_node->next = 0;
	return (new_node);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
    t_env	*tmp;

    if (!alst || !new)
        return ;
    if (!*alst)
    {
        *alst = new;
        return ;
    }
    tmp = *alst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void   printexport(void)
{
    while(g_gfl.env)
    {
        printf("declare -x %s=\"%s\"\n",g_gfl.env->name,g_gfl.env->value);
        g_gfl.env = g_gfl.env->next;
    }
    while(g_gfl.exp)
    {
        printf("declare -x %s=\"%s\"\n",g_gfl.exp->name,g_gfl.exp->value);
        g_gfl.exp = g_gfl.exp->next;
    }
}

void    export(char **str)
{
    if(!str || !*str)
    {
        printexport();
        return ;
    }
    
}

int main(int ac , char **av,char **env)
{
    t_env *head;
    g_gfl.exp = 0;
    g_gfl.env = ft_envnew(ft_split(*env,'='));
    head = g_gfl.env;
    // printf("%s and %s\n",head->name,head->value);
    // g_gfl.env = g_gfl.env->next;
    env++;
    while(*env)
    {
        ft_envadd_back(&g_gfl.env,ft_envnew(ft_split(*env,'=')));
        env++;
    }
    g_gfl.env = head;
    export(0);
    return (0);
}