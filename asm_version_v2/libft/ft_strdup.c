/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:56:05 by iosypenk          #+#    #+#             */
/*   Updated: 2017/10/29 12:56:10 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s1[i])
		i++;
	if (!(s2 = (char *)malloc(sizeof(*s1) * (i + 1))))
		return (NULL);
	while (s1[k])
	{
		s2[k] = s1[k];
		k++;
	}
	s2[k] = '\0';
	return (s2);
}
