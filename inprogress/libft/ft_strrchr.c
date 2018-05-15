/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:38:06 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/01 16:38:15 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	a;

	i = 0;
	a = c;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == c)
			return (&((char*)s)[i]);
		i--;
	}
	if (s[0] == a)
		return ((char *)s);
	return (NULL);
}
