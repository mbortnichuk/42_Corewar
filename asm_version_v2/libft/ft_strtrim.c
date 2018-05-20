/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 07:45:05 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/09 07:45:08 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	size_t	end;
	size_t	begin;
	size_t	len;

	if (!(s))
		return (NULL);
	end = ft_strlen(s) - 1;
	begin = 0;
	while (ft_isspace(s[begin]) == 1)
		begin++;
	if (begin == end + 1)
	{
		if (!(new = ft_strnew(0)))
			return (NULL);
		return (new);
	}
	while (ft_isspace(s[end]) == 1)
		end--;
	len = end - begin + 1;
	if (!(new = ft_strnew(len)))
		return (NULL);
	ft_strncpy(new, &s[begin], len);
	return (new);
}
