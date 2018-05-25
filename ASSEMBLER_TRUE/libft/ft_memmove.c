/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:34:15 by iosypenk          #+#    #+#             */
/*   Updated: 2017/10/30 17:34:19 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((unsigned char *)dst <= (unsigned char *)src)
		ft_memcpy((unsigned char *)dst, (const unsigned char *)src, len);
	else
	{
		while (len--)
		{
			(((unsigned char *)dst)[len] = ((const unsigned char *)src)[len]);
		}
	}
	return (dst);
}
