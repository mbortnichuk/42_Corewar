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
	char	*strr;

	strr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			strr = (char *)s;
		s++;
	}
	if (*s == (char)c)
		strr = (char *)s;
	return (strr);
}
