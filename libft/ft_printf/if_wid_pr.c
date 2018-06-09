/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 09:39:21 by iosypenk          #+#    #+#             */
/*   Updated: 2018/01/04 09:39:28 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			if_as(va_list ap, t_type *k, int n)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	if (n == k->nb_w[i])
	{
		if (!(k->w = va_arg(ap, int)))
			k->w = 0;
		if (k->w < 0)
		{
			k->w *= -1;
			k->minus = 1;
		}
		k->width = 1;
		i++;
	}
	if (n == k->nb_p[j])
	{
		if (!(k->p = va_arg(ap, int)))
			k->p = 0;
		k->prec = 1;
		j++;
	}
	return ;
}

static void		prec_for_s(t_type *k)
{
	char	*tmp;
	int		i;

	tmp = ft_strnew(k->p);
	i = -1;
	while (++i < k->p)
		tmp[i] = k->res[i];
	ft_strdel(&k->res);
	k->res = tmp;
	k->ln = ft_strlen(k->res);
}

void			if_prec(t_type *k)
{
	char	*tmp;
	int		i;
	int		j;

	if (k->p == 0 && k->res[0] == '0')
	{
		k->res[0] = '\0';
		return ;
	}
	if (k->p >= 0 && k->ln < k->p && k->no_tp != -1 &&
		k->tp != 's' && k->tp != 'S')
	{
		tmp = ft_strnew(k->p);
		i = 0;
		while (i < (k->p - k->ln))
			tmp[i++] = '0';
		j = 0;
		while (i < k->p)
			tmp[i++] = k->res[j++];
		ft_strdel(&k->res);
		k->res = tmp;
	}
	if ((k->tp == 's' || k->tp == 'c' || k->tp == 'S') &&
		k->p >= 0 && k->p < k->ln)
		prec_for_s(k);
}

static void		width_for_s(t_type *k)
{
	char	*tmp;
	int		i;
	int		j;

	if (k->width == 0 || k->w < (int)ft_strlen(k->res))
		return ;
	tmp = ft_strnew(k->w);
	ft_memset(tmp, ' ', k->w);
	i = 0;
	j = k->w - ft_strlen(k->res);
	while (k->res[i])
		tmp[j++] = k->res[i++];
	ft_strdel(&k->res);
	k->res = tmp;
}

void			if_width(t_type *k)
{
	char	*tmp;
	int		i;
	int		j;

	if (k->width == 0)
		return ;
	(k->tp == 's' || k->tp == 'c' || k->tp == 'S') ? width_for_s(k) : 0;
	if (k->ln <= k->w && k->p < k->w &&
		k->tp != 's' && k->tp != 'c' && k->tp != 'S')
	{
		tmp = ft_strnew(k->w);
		ft_memset(tmp, ' ', k->w);
		i = 0;
		if (k->ln < k->p && k->p < k->w)
			j = k->w - k->p;
		else
			j = k->w - k->ln;
		while (k->res[i])
			tmp[j++] = k->res[i++];
		ft_strdel(&k->res);
		k->res = tmp;
	}
}
