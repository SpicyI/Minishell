/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:14:12 by del-khay          #+#    #+#             */
/*   Updated: 2023/02/03 21:24:06 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freenode(t_export *node)
{
	if (!node)
        return ;
    if (node->value){
    printf("value = %s\n", node->value);
        free(node->value);}
    // if (node->name)
    // {
    //     printf("name = %s\n", node->name);
    //     free(node->name);
    // }
    if (node)
    {
    printf("here as well\n");    
	free(node);
    }
}

void	freenode2(t_not_env *node)
{
	if(!node)
        return ;
    if (node->name)
        free(node->name);
    if (node->value)
	    free(node->value);
	free(node);
}