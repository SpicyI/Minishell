/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:18:24 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/03 14:04:10 by del-khay         ###   ########.fr       */
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

t_export	*ft_exportnew(char **content)
{
	t_export	*new_node;

	new_node = (t_export *) malloc(sizeof(t_export));
	if (!new_node)
		return (0);
	new_node->name = content[0];
    new_node->value = 0;
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
void	ft_exportadd_back(t_export **alst, t_export *new)
{
    t_export	*tmp;

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
        printf("declare -x %s=\n",g_gfl.exp->name);
        g_gfl.exp = g_gfl.exp->next;
    }
}

char **ft_export_spliter(char *str)
{
    int i;
    char **tab;
    
    i = 0;
    tab = (char **) ft_calloc(2, sizeof(char *));
    if (!str || !*str)
        return (0);
    tab[0] = (char *) ft_calloc((ft_dstrlen(str,'=') + 1), sizeof(char));
    while (str[i] != '=')
    {
        tab[0][i] = str[i];
        i++;
    }
    str = str + i + 1;
    tab[1] = (char *) ft_calloc((ft_strlen(str) + 1), sizeof(char));
    i = 0;
    while (str[i])
    {
        tab[1][i] = str[i];
        i++;
    }
    return (tab);
}

int check_name(char *name)
{
    if (!name || !*name)
        return (0);
    if (!ft_isalpha(*name) && *name != '_')
        return (0);
    while (*name)
    {
        if (!ft_isalnum(*name) && *name != '_')
            return (0);
        name++;
    }
    return (1);
}

void    freenode(t_export *node)
{
    free(node->name);
    free(node);
}
void    freenode2(t_not_env *node)
{
    free(node->name);
    free(node->value);
    free(node);
}
int is_env(char **tab)
{
    t_env       *tmp;
    t_not_env   *tmp0;
    t_export    *tmp1;
    void    *holder;

    tmp = g_gfl.env;
    tmp1 = g_gfl.exp;
    tmp0 = g_gfl.not_env;
    // case where name already in the env and need to be updated with the new val
    while(tmp)
    {
        if(!ft_strncmp(tab[0],tmp->name,ft_strlen(tab[0])))
        {
 
            tmp->value = tab[1];
            return (1);
        }
        tmp = tmp->next;
    }
    //case where name is exported but has no value
    while (tmp1)
    {
        
        if(!ft_strncmp(tab[0],tmp1->name,ft_strlen(tab[0])))
        {
           ((t_export *)holder)->next = tmp1->next;
           freenode(tmp1);
           return (0);
        }
        holder = tmp1;
        tmp1 = tmp1->next;
    }
    //case where name not a env val
    while (tmp0)
    {
        // printf("tab[0] = %s , name = %s, len = %d",tab[0],tmp0->name,ft_strlen(tab[0]));
        if(!ft_strncmp(tab[0],tmp0->name,ft_strlen(tab[0])))
        {
           ((t_not_env *)holder)->next = tmp0->next;
           freenode2(tmp0);
           return (0);
        }
        holder = tmp0;
        tmp0 = tmp0->next;
    }
    
    return (0);
}

int     parss_export(char *str)
{
    int i;
    char **tab;
    
    if (ft_strchr(str , '='))
    {
        tab = ft_export_spliter(str);
        if (!check_name(tab[0]))
        {
            printf("export: `%s': not a valid identifier\n",tab[0]);
            return(1);
        }
        else if (!is_env(tab))
                ft_envadd_back(&g_gfl.env,ft_envnew(tab));
    }
    else
    {
        if (check_name(str))
            ft_exportadd_back(&g_gfl.exp,ft_exportnew(&str));
        else
            printf("export: `%s': not a valid identifier\n",str);
    }

    return (0);
}

void    export(char **str)
{
    int optn;
    if(!str || !*str)
    {
        printexport();
        return ;
    }
    while (*str)
    {
        parss_export(*str);
        str++;
    }
}

int main(int ac , char **av,char **env)
{
    if(!env || !*env)
        return (printf("no env\n"));
    
    t_env *head;
    g_gfl.exp = 0;
    g_gfl.not_env = 0;
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
    export(av + 1);
    export(0);
    return (0);
}