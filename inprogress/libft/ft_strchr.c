/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:44:42 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/01 15:44:49 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;
	char	a;

	i = 0;
	j = 0;
	a = c;
	if (!s)
		return (NULL);
	while (s[j])
		j++;
	j = j + 1;
	while (i < j)
	{
		if (s[i] == c)
			return (&((char*)s)[i]);
		i++;
	}
	return (NULL);
}
