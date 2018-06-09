/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:13:30 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/10 16:13:33 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	size_t	i;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = (t_list *)malloc(sizeof(content) * content_size)))
		{
			free(new);
			new = NULL;
			return (NULL);
		}
		i = -1;
		while (++i < content_size)
			((unsigned char *)new->content)[i] = ((unsigned char *)content)[i];
		new->content_size = content_size;
	}
	return (new);
}
