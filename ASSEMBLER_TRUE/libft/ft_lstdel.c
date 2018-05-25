/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:14:19 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/10 16:14:22 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*go;

	if (!alst)
		return ;
	while (*alst)
	{
		go = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = go;
	}
}
