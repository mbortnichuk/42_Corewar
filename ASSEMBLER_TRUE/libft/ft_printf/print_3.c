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

void		print_bx(va_list ap, t_type *k)
{
	k->tp = 'X';
	k->plus = 0;
	k->space = 0;
	if (k->j == 1 || k->z == 1 || k->ll == 1 || k->l == 1 ||
		k->hh == 1 || k->h == 1)
	{
		(k->z == 1) ? (k->res = ui(va_arg(ap, size_t), 16, 2)) : 0;
		(k->j == 1) ? (k->res = ui(va_arg(ap, uintmax_t), 16, 2)) : 0;
		(k->ll == 1) ? (k->res = ui(va_arg(ap, unsigned long long), 16, 2)) : 0;
		(k->l == 1) ? (k->res = ui(va_arg(ap, unsigned long), 16, 2)) : 0;
		(k->h == 1) ? (k->res = ui((unsigned short)va_arg(ap, int), 16, 2)) : 0;
		(k->hh == 1) ? (k->res = ui((unsigned char)va_arg(ap, int), 16, 2)) : 0;
	}
	else
		k->res = ui(va_arg(ap, unsigned int), 16, 2);
	k->res[0] == '0' ? k->octo = 0 : 0;
}

void		print_c(va_list ap, t_type *k)
{
	k->prec = 0;
	k->plus = 0;
	k->space = 0;
	k->tp = 'c';
	k->c = va_arg(ap, int);
	k->res = ft_strnew(1);
	k->res[0] = k->c;
	if (k->c == 0)
	{
		k->w--;
		if (k->minus == 1)
		{
			write(1, "\0", 1);
			k->ret_nb++;
		}
	}
}

void		print_bc(va_list ap, t_type *k)
{
	int		n;
	int		tmp;

	k->plus = 0;
	k->space = 0;
	k->prec = 0;
	k->tp = 'c';
	tmp = 0;
	k->res = ft_strnew(0);
	n = va_arg(ap, int);
	if (n == 0)
	{
		k->c = 0;
		k->w--;
	}
	if (n >= 0 && n < 128)
		one(k, &n, tmp);
	else if (n > 160 && n < 2048)
		two(k, &n, tmp);
	else if (n >= 2048 && n < 65536)
		three(k, &n, tmp);
	else
		four(k, &n, tmp);
}

void		print_s(va_list ap, t_type *k)
{
	char	*tmp;

	k->plus = 0;
	k->space = 0;
	k->tp = 's';
	tmp = va_arg(ap, char *);
	if (tmp == NULL)
		k->res = ft_strdup("(null)");
	else
		k->res = ft_strdup(tmp);
}

void		print_bs(va_list ap, t_type *k)
{
	int		*n;
	int		tmp;
	int		wid;
	int		pr;

	k->plus = 0;
	k->space = 0;
	k->tp = 'S';
	tmp = 0;
	wid = 0;
	k->res = ft_strnew(0);
	pr = k->p == 0 ? 2097152 : k->p;
	if (!(n = va_arg(ap, int *)))
	{
		k->res = ft_strdup("(null)");
		return ;
	}
	while (*n)
	{
		(*n >= 0 && *n < 128 && (wid++ <= pr)) ? one(k, n, tmp) : 0;
		(*n > 160 && *n < 2048 && (wid += 2) <= pr) ? two(k, n, tmp) : 0;
		(*n >= 2048 && *n < 65536 && (wid += 3) <= pr) ? three(k, n, tmp) : 0;
		(*n >= 65536 && *n < 2097152 && (wid += 4) <= pr) ? four(k, n, tmp) : 0;
		n++;
	}
}
