/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:01:16 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/21 17:01:18 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			save_n(va_list ap, t_type *k)
{
	int		*n;

	n = va_arg(ap, void *);
	*n = k->ret_nb;
}

static int		ft_intlen(intmax_t nb, int base)
{
	int		count;

	count = 0;
	if (nb <= 0 && base == 10)
		count = 1;
	while (nb != 0)
	{
		nb = nb / base;
		count++;
	}
	return (count);
}

static int		ft_uintlen(uintmax_t nb, int base)
{
	int		count;

	count = 0;
	if (nb == 0)
		count = 1;
	while (nb != 0)
	{
		nb = nb / base;
		count++;
	}
	return (count);
}

char			*ib(intmax_t value, int base)
{
	char			*b;
	uintmax_t		nb;
	intmax_t		len;
	char			*res;

	nb = value < 0 ? -value : value;
	b = "0123456789ABCDEF";
	len = ft_intlen(value, base);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len-- > 0)
	{
		res[len] = b[nb % base];
		nb = nb / base;
	}
	(value < 0) ? res[0] = '-' : 0;
	res[ft_intlen(value, base)] = '\0';
	return (res);
}

char			*ui(uintmax_t value, int base, int c)
{
	char		*b;
	uintmax_t	nb;
	uintmax_t	len;
	char		*res;

	nb = value;
	if (c == 2)
		b = "0123456789ABCDEF";
	else
		b = "0123456789abcdef";
	len = ft_uintlen(value, base);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len-- > 0)
	{
		res[len] = b[nb % base];
		nb = nb / base;
	}
	res[ft_uintlen(value, base)] = '\0';
	return (res);
}
