/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 19:52:07 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/28 19:52:15 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_priority(t_type *k)
{
	if (k->z == 1)
	{
		k->j = 0;
		k->ll = 0;
		k->l = 0;
		k->hh = 0;
		k->h = 0;
	}
	if (k->j == 1)
	{
		k->ll = 0;
		k->l = 0;
		k->hh = 0;
		k->h = 0;
	}
	if (k->ll == 1 || k->l == 1)
	{
		k->hh = 0;
		k->h = 0;
	}
	return ;
}

static void		check_h_hh(char *sp, t_type *k)
{
	int		i;
	int		j;
	int		count;

	if (!sp)
		return ;
	i = 0;
	while (sp[i])
	{
		if (sp[i] == 'h')
		{
			j = 0;
			count = 0;
			while (sp[j + i])
			{
				(sp[j + i] == 'h') ? count++ : 0;
				j++;
			}
			(count % 2 == 0) ? (k->hh = 1) : 0;
			(count % 2 != 0) ? (k->h = 1) : 0;
			break ;
		}
		i++;
	}
	return ;
}

static void		check_l_ll(char *sp, t_type *k)
{
	int		i;
	int		j;
	int		count;

	if (!sp)
		return ;
	i = -1;
	while (sp[++i])
		if (sp[i] == 'l')
		{
			j = 0;
			count = 0;
			while (sp[j + i] && (sp[j + i] == ' ' || sp[j + i] == 'l'))
			{
				(count % 2 != 0) ? k->ll = 1 : 0;
				(k->ll == 1) ? k->l = 0 : 0;
				(count % 2 == 0 && k->ll == 0) ? k->l = 1 : 0;
				(sp[j + i] == 'l') ? count++ : 0;
				j++;
			}
			break ;
		}
	return ;
}

void			get_length(char *sp, t_type *k)
{
	int		i;

	if (!sp)
		return ;
	i = 0;
	while (sp[i])
	{
		(sp[i] == 'j') ? k->j = 1 : 0;
		(sp[i] == 'z') ? k->z = 1 : 0;
		check_l_ll(sp + i, k);
		i++;
	}
	check_h_hh(sp, k);
	check_priority(k);
	return ;
}

void			get_width_prec(va_list ap, char *sp, t_type *k)
{
	int		i;
	int		j;
	int		l;
	int		n;

	i = -1;
	j = 1;
	l = 1;
	n = 1;
	while (sp[++i])
	{
		k->nb_p[j] = (sp[i] == '*' && sp[i - 1] == '.') ? ++k->aster : 0;
		k->nb_w[l] = (sp[i] == '*' && sp[i - 1] != '.') ? ++k->aster : 0;
		sp[i] == '.' ? k->p = 0 : 0;
		sp[i] == '.' && ft_isdigit(sp[i + 1]) ? k->p = ft_atoi(sp + i + 1) : 0;
		if (ft_isdigit(sp[i]) && sp[i - 1] != '.')
			if (((ft_isdigit(sp[i]) && !ft_isdigit(sp[i - 1])) ||
				(ft_isdigit(sp[i]) && sp[i - 1] == '0')) && sp[i] != '0')
			{
				k->width = 1;
				k->w = ft_atoi(sp + i);
			}
		(sp[i] == '*' && k->aster != -1 && n <= k->aster) ? if_as(ap, k, n) : 0;
		(sp[i] == '*' && k->aster != -1 && n <= k->aster) ? n++ : 0;
	}
}
