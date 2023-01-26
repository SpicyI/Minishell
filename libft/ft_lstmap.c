/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:53:51 by del-khay          #+#    #+#             */
/*   Updated: 2022/10/15 19:20:26 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*carry;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		carry = ft_lstnew(f(lst->content));
		if (!carry)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, carry);
		lst = lst->next;
	}	
	return (new);
}
