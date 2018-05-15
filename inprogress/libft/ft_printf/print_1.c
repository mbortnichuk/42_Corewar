/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 12:26:45 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/29 12:26:52 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus_d_i(t_type *k)
{
	char	*tmp;
	int		i;

	tmp = ft_strnew(ft_strlen(k->res) - 1);
	i = 0;
	while (k->res[i])
	{
		tmp[i] = k->res[i + 1];
		i++;
	}
	ft_strdel(&k->res);
	k->res = tmp;
	k->sign = 1;
	k->plus = 1;
}

void		print_d_i(va_list ap, t_type *k)
{
	k->octo = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ib(va_arg(ap, size_t), 10)) : 0;
		(k->j == 1) ? (k->res = ib(va_arg(ap, intmax_t), 10)) : 0;
		(k->ll == 1) ? (k->res = ib(va_arg(ap, long long), 10)) : 0;
		(k->l == 1) ? (k->res = ib(va_arg(ap, long), 10)) : 0;
		(k->h == 1) ? (k->res = ib((short)va_arg(ap, int), 10)) : 0;
		(k->hh == 1) ? (k->res = ib((signed char)va_arg(ap, int), 10)) : 0;
	}
	else
		k->res = ib(va_arg(ap, int), 10);
	if (k->res[0] == '-')
		print_minus_d_i(k);
}

void		print_bd(va_list ap, t_type *k)
{
	k->octo = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ib(va_arg(ap, size_t), 10)) : 0;
		(k->j == 1) ? (k->res = ib(va_arg(ap, intmax_t), 10)) : 0;
		(k->ll == 1) ? (k->res = ib(va_arg(ap, long long), 10)) : 0;
		(k->l == 1) ? (k->res = ib(va_arg(ap, long), 10)) : 0;
		(k->h == 1) ? (k->res = ib(va_arg(ap, long), 10)) : 0;
		(k->hh == 1) ? (k->res = ib(va_arg(ap, long), 10)) : 0;
	}
	else
		k->res = ib(va_arg(ap, long), 10);
}

void		print_p(va_list ap, t_type *k)
{
	k->plus = 0;
	k->space = 0;
	k->octo = 1;
	k->res = ui(va_arg(ap, uintmax_t), 16, 1);
}

void		print_b(va_list ap, t_type *k)
{
	k->res = ui(va_arg(ap, unsigned int), 2, 1);
	if (ft_strlen(k->res) < 8)
	{
		k->width = 1;
		k->w = 8;
		k->zero = 1;
	}
}
