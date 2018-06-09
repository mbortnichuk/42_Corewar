/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:52:00 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/12 11:52:04 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen(int nb, int base)
{
	int		count;

	count = 0;
	while (nb != 0)
	{
		nb = nb / base;
		count++;
	}
	return (count);
}

char			*ft_itoa_base(int value, int base)
{
	char			*b;
	unsigned int	nb;
	unsigned int	len;
	char			*res;

	nb = value;
	b = "0123456789ABCDEF";
	len = ft_intlen(value, base);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len-- > 0)
	{
		res[len] = b[nb % base];
		nb = nb / base;
	}
	res[ft_intlen(value, base)] = '\0';
	return (res);
}
