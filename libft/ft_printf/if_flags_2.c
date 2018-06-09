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

static void		octo_no_width(t_type *k)
{
	int		i;
	int		j;
	int		m;
	char	*tmp;

	tmp = ft_strnew(ft_strlen(k->res) + 2);
	if (k->tp == 'o' || k->tp == 'x' || k->tp == 'X' || k->tp == 'p')
		tmp[0] = '0';
	(k->tp == 'x' || k->tp == 'p') ? tmp[1] = 'x' : 0;
	k->tp == 'X' ? tmp[1] = 'X' : 0;
	i = (k->tp == 'x' || k->tp == 'X' || k->tp == 'p') ? 2 : 1;
	j = 0;
	if (k->minus == 1 && k->ln < k->w - 1)
		m = (k->tp == 'o') ? k->w - 1 : k->w - 2;
	else if (k->ln < k->p)
		m = k->p;
	else
		m = k->ln;
	while (k->res[j] && j < m)
		tmp[i++] = k->res[j++];
	ft_strdel(&k->res);
	k->res = tmp;
	return ;
}

static void		octo_half_width(t_type *k)
{
	int		i;
	char	*tmp;

	k->tp != 'o' ? tmp = ft_strnew(ft_strlen(k->res) + 1) : 0;
	k->tp != 'o' ? tmp[0] = '0' : 0;
	i = 0;
	k->res[0] = k->tp == 'o' ? '0' : 'x';
	k->tp == 'X' ? k->res[0] = 'X' : 0;
	while (k->res[i] && k->tp != 'o')
	{
		tmp[i + 1] = k->res[i];
		i++;
	}
	k->tp != 'o' ? ft_strdel(&k->res) : 0;
	k->tp != 'o' ? k->res = tmp : 0;
	return ;
}

static void		octo_with_width(t_type *k)
{
	int		j;

	if (k->tp != 'o' && k->ln < k->w && k->prec == 0 && k->zero == 1)
	{
		k->res[0] = '0';
		k->res[1] = (k->tp == 'X') ? 'X' : 'x';
		return ;
	}
	if ((k->ln + 1 == k->w) || (k->w - k->p < 2))
	{
		octo_half_width(k);
		return ;
	}
	j = (k->ln < k->p) ? k->w - k->p : k->w - k->ln;
	(k->tp == 'o' && k->p <= k->ln) ? j-- : 0;
	k->tp == 'o' ? k->res[j] = '0' : 0;
	(k->tp == 'x' || k->tp == 'p') ? k->res[j - 1] = 'x' : 0;
	(k->tp == 'x' || k->tp == 'p') ? k->res[j - 2] = '0' : 0;
	(k->tp == 'X') ? k->res[j - 1] = 'X' : 0;
	(k->tp == 'X') ? k->res[j - 2] = '0' : 0;
	return ;
}

void			if_octo(t_type *k)
{
	if ((k->tp == 'o') && k->res[0] == '0')
		return ;
	if (k->tp == 'o' || k->tp == 'x' || k->tp == 'X' || k->tp == 'p')
	{
		if (k->ln < k->w && k->minus == 0 && k->w > k->p)
		{
			octo_with_width(k);
		}
		else
		{
			if (k->ln < k->p && k->tp == 'o')
				return ;
			octo_no_width(k);
		}
	}
	return ;
}
