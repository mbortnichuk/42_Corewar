/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:15:13 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/10 16:15:15 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*go;

	if (!lst)
		return (NULL);
	go = f(lst);
	new = go;
	while (lst->next)
	{
		lst = lst->next;
		go->next = f(lst);
		go = go->next;
	}
	return (new);
}
