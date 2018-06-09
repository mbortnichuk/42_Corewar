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

void		print_u(va_list ap, t_type *k)
{
	k->plus = 0;
	k->space = 0;
	k->octo = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ui(va_arg(ap, size_t), 10, 1)) : 0;
		(k->j == 1) ? (k->res = ui(va_arg(ap, uintmax_t), 10, 1)) : 0;
		(k->ll == 1) ? (k->res = ui(va_arg(ap, unsigned long long), 10, 1)) : 0;
		(k->l == 1) ? (k->res = ui(va_arg(ap, unsigned long), 10, 1)) : 0;
		(k->h == 1) ? (k->res = ui((unsigned short)va_arg(ap, int), 10, 1)) : 0;
		(k->hh == 1) ? (k->res = ui((unsigned char)va_arg(ap, int), 10, 1)) : 0;
	}
	else
		k->res = ui(va_arg(ap, unsigned int), 10, 1);
}

void		print_bu(va_list ap, t_type *k)
{
	k->plus = 0;
	k->space = 0;
	k->octo = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ui(va_arg(ap, size_t), 10, 1)) : 0;
		(k->j == 1) ? (k->res = ui(va_arg(ap, uintmax_t), 10, 1)) : 0;
		(k->ll == 1) ? (k->res = ui(va_arg(ap, unsigned long long), 10, 1)) : 0;
		(k->l == 1) ? (k->res = ui(va_arg(ap, unsigned long), 10, 1)) : 0;
		(k->h == 1) ? (k->res = ui(va_arg(ap, unsigned long), 10, 1)) : 0;
		(k->hh == 1) ? (k->res = ui(va_arg(ap, unsigned long), 10, 1)) : 0;
	}
	else
		k->res = ui(va_arg(ap, unsigned long), 10, 1);
}

void		print_o(va_list ap, t_type *k)
{
	k->tp = 'o';
	k->plus = 0;
	k->space = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ui(va_arg(ap, size_t), 8, 1)) : 0;
		(k->j == 1) ? (k->res = ui(va_arg(ap, uintmax_t), 8, 1)) : 0;
		(k->ll == 1) ? (k->res = ui(va_arg(ap, unsigned long long), 8, 1)) : 0;
		(k->l == 1) ? (k->res = ui(va_arg(ap, unsigned long), 8, 1)) : 0;
		(k->h == 1) ? (k->res = ui((unsigned short)va_arg(ap, int), 8, 1)) : 0;
		(k->hh == 1) ? (k->res = ui((unsigned char)va_arg(ap, int), 8, 1)) : 0;
	}
	else
		k->res = ui(va_arg(ap, unsigned int), 8, 1);
}

void		print_bo(va_list ap, t_type *k)
{
	k->tp = 'o';
	k->plus = 0;
	k->space = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ui(va_arg(ap, size_t), 8, 1)) : 0;
		(k->j == 1) ? (k->res = ui(va_arg(ap, uintmax_t), 8, 1)) : 0;
		(k->ll == 1) ? (k->res = ui(va_arg(ap, unsigned long long), 8, 1)) : 0;
		(k->l == 1) ? (k->res = ui(va_arg(ap, unsigned long), 8, 1)) : 0;
		(k->h == 1) ? (k->res = ui(va_arg(ap, unsigned long), 8, 1)) : 0;
		(k->hh == 1) ? (k->res = ui(va_arg(ap, unsigned long), 8, 1)) : 0;
	}
	else
		k->res = ui(va_arg(ap, unsigned long), 8, 1);
}

void		print_x(va_list ap, t_type *k)
{
	k->tp = 'x';
	k->plus = 0;
	k->space = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ui(va_arg(ap, size_t), 16, 1)) : 0;
		(k->j == 1) ? (k->res = ui(va_arg(ap, uintmax_t), 16, 1)) : 0;
		(k->ll == 1) ? (k->res = ui(va_arg(ap, unsigned long long), 16, 1)) : 0;
		(k->l == 1) ? (k->res = ui(va_arg(ap, unsigned long), 16, 1)) : 0;
		(k->h == 1) ? (k->res = ui((unsigned short)va_arg(ap, int), 16, 1)) : 0;
		(k->hh == 1) ? (k->res = ui((unsigned char)va_arg(ap, int), 16, 1)) : 0;
	}
	else
		k->res = ui(va_arg(ap, unsigned int), 16, 1);
	if (k->res[0] == '0')
	{
		ft_strdel(&k->res);
		k->octo = 0;
		k->res = (char *)malloc(sizeof(char) * 2);
		k->res[0] = '0';
		k->res[1] = '\0';
	}
}
