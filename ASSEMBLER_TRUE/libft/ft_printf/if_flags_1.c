/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 12:57:28 by iosypenk          #+#    #+#             */
/*   Updated: 2018/01/10 12:57:31 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	else_for_plus_space(t_type *k, char *tmp)
{
	int		i;
	int		j;
	int		m;

	i = 1;
	j = 0;
	if (k->ln < k->w && k->p < k->w)
		m = k->w - 1;
	else if (k->ln < k->p)
		m = k->p;
	else
		m = k->ln;
	while (k->res[j] && j < m)
		tmp[i++] = k->res[j++];
	ft_strdel(&k->res);
	k->res = tmp;
}

void		if_plus(t_type *k)
{
	int		j;
	char	*tmp;

	if (k->ln < k->w && k->minus == 0 && k->p < k->w)
	{
		j = (k->ln < k->p) ? k->w - k->p : k->w - k->ln;
		k->zero == 1 ? j = 1 : 0;
		(k->ln < k->p && k->zero == 1) ? j = k->w - k->p : 0;
		k->res[j - 1] = '+';
		k->sign == 1 ? k->res[j - 1] = '-' : 0;
	}
	else
	{
		tmp = ft_strnew(ft_strlen(k->res) + 1);
		tmp[0] = '+';
		k->sign == 1 ? tmp[0] = '-' : 0;
		else_for_plus_space(k, tmp);
	}
}

void		if_space(t_type *k)
{
	int		j;
	char	*tmp;

	if (k->plus == 0)
	{
		if (k->ln < k->w && k->minus == 0 && k->p < k->w)
		{
			j = k->ln < k->p ? k->w - k->p : k->w - k->ln;
			k->res[j - 1] = ' ';
		}
		else
		{
			tmp = ft_strnew(ft_strlen(k->res) + 1);
			tmp[0] = ' ';
			else_for_plus_space(k, tmp);
		}
	}
}

void		if_minus(t_type *k)
{
	char	*tmp;
	int		i;
	int		j;
	int		m;

	if ((k->ln < k->w && k->w > k->p) ||
		(k->tp == 'S' && k->w > (int)ft_strlen(k->res)))
	{
		tmp = ft_strnew(k->w);
		i = 0;
		j = k->ln < k->p ? k->w - k->p : k->w - k->ln;
		(k->tp == 's' || k->tp == 'c' || k->tp == 'S') ? j = k->w - k->ln : 0;
		while (k->res[j])
			tmp[i++] = k->res[j++];
		j = 0;
		m = k->ln < k->p ? k->w - k->p : k->w - k->ln;
		(k->tp == 's' || k->tp == 'c' || k->tp == 'S') ? m = k->w - k->ln : 0;
		while (j < m && i < k->w)
			tmp[i++] = k->res[j++];
		ft_strdel(&k->res);
		k->res = tmp;
	}
}

void		if_zero(t_type *k)
{
	int		i;
	int		n;

	if ((k->ln < k->w && k->minus == 0 && (k->p < 0 || k->prec == 0)) ||
		(k->ln < k->w && k->minus == 0 && (k->tp == 's' || k->tp == 'S')))
	{
		i = 0;
		n = k->w - k->ln;
		(k->space == 1 || k->plus == 1) ? i = 1 : 0;
		while (i < n)
		{
			k->res[i] = '0';
			i++;
		}
	}
}
