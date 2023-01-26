/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 01:09:00 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/15 19:35:21 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*carry;

	if (!lst || !del)
		return ;
	while (*lst)
	{	
		carry = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = carry;
	}
	*lst = NULL;
}
