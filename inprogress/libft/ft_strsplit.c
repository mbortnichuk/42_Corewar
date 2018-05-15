/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:46:00 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/09 09:46:02 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	if (!(res = (char **)malloc(sizeof(*res) * (ft_countwords(s, c) + 1))))
		return (NULL);
	while (i < ft_countwords(s, c))
	{
		if (!(str = (char *)malloc(sizeof(str) * (ft_countchar(s, c) + 1))))
			return (NULL);
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
			str[i++] = *s++;
		str[i] = '\0';
		res[j++] = str;
		i = 0;
	}
	res[j] = 0;
	return (res);
}
