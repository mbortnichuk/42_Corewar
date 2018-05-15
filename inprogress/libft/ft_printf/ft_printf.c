/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 11:37:34 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/09 11:37:37 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		clear_k(t_type *k)
{
	k->res = NULL;
	k->tp = 0;
	k->no_tp = 0;
	k->plus = 0;
	k->minus = 0;
	k->space = 0;
	k->octo = 0;
	k->zero = 0;
	k->aster = 0;
	k->nb_w = NULL;
	k->nb_p = NULL;
	k->width = 0;
	k->w = 0;
	k->prec = 0;
	k->p = 0;
	k->hh = 0;
	k->h = 0;
	k->l = 0;
	k->ll = 0;
	k->j = 0;
	k->z = 0;
	k->ln = 0;
	k->sign = 0;
	k->c = 127;
}

static void		check_type(va_list ap, t_type *k)
{
	if (!k)
		return ;
	(k->tp == 'i' || k->tp == 'd') ? print_d_i(ap, k) : 0;
	(k->tp == 'D') ? print_bd(ap, k) : 0;
	(k->tp == 'u') ? print_u(ap, k) : 0;
	(k->tp == 'U') ? print_bu(ap, k) : 0;
	(k->tp == 'o') ? print_o(ap, k) : 0;
	(k->tp == 'O') ? print_bo(ap, k) : 0;
	(k->tp == 'x') ? print_x(ap, k) : 0;
	(k->tp == 'X') ? print_bx(ap, k) : 0;
	(k->tp == 'c' && k->l != 1) ? print_c(ap, k) : 0;
	((k->tp == 'c' && k->l == 1) || (k->tp == 'C')) ? print_bc(ap, k) : 0;
	(k->tp == 'n') ? save_n(ap, k) : 0;
	(k->tp == 'b') ? print_b(ap, k) : 0;
	(k->tp == 's' && k->l != 1) ? print_s(ap, k) : 0;
	(k->tp == 'S' || (k->tp == 's' && k->l == 1)) ? print_bs(ap, k) : 0;
	(k->tp == 'p') ? print_p(ap, k) : 0;
	return ;
}

static void		string_processing(t_type *k)
{
	k->ln = ft_strlen(k->res);
	k->prec == 1 ? if_prec(k) : 0;
	k->width == 1 ? if_width(k) : 0;
	k->minus == 1 ? if_minus(k) : 0;
	k->plus == 1 ? if_plus(k) : 0;
	k->space == 1 ? if_space(k) : 0;
	k->zero == 1 ? if_zero(k) : 0;
	k->octo == 1 ? if_octo(k) : 0;
	k->ret_nb = (k->ret_nb + ft_strlen(k->res));
	(k->tp != 'n') ? ft_putstr(k->res) : 0;
	if ((k->tp == 'c' || k->tp == 'C') && k->c == 0 && k->minus == 0)
	{
		write(1, "\0", 1);
		k->ret_nb++;
	}
	ft_strdel(&k->res);
}

static void		specif_processing(va_list ap, t_type *k, char *sp)
{
	get_length(sp, k);
	get_type(sp, k);
	k->nb_w = ft_strnew(k->aster);
	k->nb_p = ft_strnew(k->aster);
	k->aster = 0;
	get_width_prec(ap, sp, k);
	ft_strdel(&k->nb_w);
	ft_strdel(&k->nb_p);
}

int				ft_printf(const char *ft, ...)
{
	va_list		ap;
	t_type		k;
	char		*sp;
	int			repeat;

	va_start(ap, ft);
	sp = NULL;
	k.ret_nb = 0;
	repeat = 1;
	while (repeat != 0)
	{
		clear_k(&k);
		(get_spec(&ft, &k, &sp) == 0) ? repeat = 0 : 0;
		if (sp != NULL)
		{
			specif_processing(ap, &k, sp);
			ft_strdel(&sp);
		}
		check_type(ap, &k);
		(k.res != NULL) ? string_processing(&k) : 0;
	}
	va_end(ap);
	return (k.ret_nb);
}
