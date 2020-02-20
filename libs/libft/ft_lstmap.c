/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:33:47 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/21 14:56:19 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;

	if (!(lst))
		return (NULL);
	if (!(new_list = ft_lstnew(f(lst->content))))
		return (NULL);
	current = new_list;
	while (lst)
	{
		if (lst->next)
		{
			if (!(new_list->next = ft_lstnew(f(lst->next->content))))
			{
				ft_lstclear(&current, del);
				return (NULL);
			}
			new_list = new_list->next;
		}
		lst = lst->next;
	}
	new_list->next = NULL;
	return (current);
}
