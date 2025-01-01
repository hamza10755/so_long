/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:08:36 by hbelaih           #+#    #+#             */
/*   Updated: 2024/09/09 14:36:00 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del) (void *))
{
	t_list	*h;
	t_list	*temp;

	h = NULL;
	while (lst)
	{
		temp = ft_lstnew((f)(lst->content));
		if (!temp)
		{
			ft_lstclear(&h, del);
			return (NULL);
		}
		ft_lstadd_back(&h, temp);
		lst = lst->next;
	}
	return (h);
}
