/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:57:23 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/09 18:57:26 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnbr(int nb)
{
	int		count;

	count = 0;
	if (nb <= 0)
		count = 1;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char				*res;
	unsigned int		len;
	unsigned int		sign;
	unsigned int		nb;

	nb = n;
	sign = 0;
	len = ft_countnbr(n);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		nb = -n;
		sign = -1;
	}
	while (len-- > ((sign == 0) ? 0 : 1))
	{
		res[len] = nb % 10 + 48;
		nb = nb / 10;
	}
	res[ft_countnbr(n)] = '\0';
	return (res);
}
