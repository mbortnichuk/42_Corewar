/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrevrange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:57:27 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/13 13:57:31 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrevrange(char *s, size_t start, size_t end)
{
	char	c;

	if (!s || s[0] == '\0')
		return ;
	while (start < end)
	{
		c = s[end];
		s[end] = s[start];
		s[start] = c;
		start++;
		end--;
	}
	return ;
}
