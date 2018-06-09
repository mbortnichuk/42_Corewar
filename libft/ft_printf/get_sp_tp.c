/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 16:46:46 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/20 16:46:49 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*cpy_spec(const char *ft, size_t start, size_t end)
{
	char	*spec;
	size_t	i;

	spec = ft_strnew(end - start + 1);
	i = 0;
	while (i <= end - start)
	{
		spec[i] = (ft + start)[i];
		i++;
	}
	return (spec);
}

static int		find_char(const char *ft, t_type *k)
{
	size_t	j;

	j = 0;
	while (ft[j])
	{
		if (ft[j] == ' ' || ft[j] == '-' || ft[j] == '+' || ft[j] == '#' ||
			ft[j] == '*' || ft[j] == '.' || ft[j] == 'h' || ft[j] == 'l' ||
			ft[j] == 'j' || ft[j] == 'z' || (ft[j] >= '0' && ft[j] <= '9'))
		{
			ft[j] == ' ' ? k->space = 1 : 0;
			ft[j] == '+' ? k->plus = 1 : 0;
			ft[j] == '-' ? k->minus = 1 : 0;
			ft[j] == '#' ? k->octo = 1 : 0;
			ft[j] == '.' ? k->prec = 1 : 0;
			ft[j] == '.' ? k->p = 0 : 0;
			ft[j] == '*' ? k->aster++ : 0;
			(!ft_isdigit(ft[j - 1]) && ft[j] == '0') ? k->zero = 1 : 0;
			j++;
			continue ;
		}
		return (j);
	}
	return (-1);
}

int				get_spec(const char **ft, t_type *k, char **sp)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while ((*ft)[i])
	{
		if ((*ft)[i] != '%' && (*ft)[i])
		{
			k->ret_nb++;
			write(1, &((*ft)[i]), 1);
		}
		if ((*ft)[i] == '%' && (*ft)[i + 1])
		{
			if ((end = find_char(*ft + i + 1, k)) != -1)
			{
				*sp = cpy_spec(*ft, (i + 1), (i + 1 + end));
				*ft = ((*ft) + (i + 2 + end));
				return (1);
			}
			break ;
		}
		i++;
	}
	return (0);
}

static int		check_specif(char tp)
{
	int			j;
	char		*valid_tp;

	j = 0;
	valid_tp = "idDuUoOxXcCnbsSp";
	if (!tp)
		return (-1);
	while (valid_tp[j])
	{
		if (tp == valid_tp[j])
			return (j);
		j++;
	}
	return (-1);
}

void			get_type(char *sp, t_type *k)
{
	int		i;

	if (!sp)
		return ;
	i = -1;
	while (sp[++i])
		if (sp[i + 1] == '\0')
			k->tp = sp[i];
	if ((k->no_tp = check_specif(k->tp)) == -1)
	{
		if (k->no_tp == -1)
		{
			k->space = 0;
			k->plus = 0;
			k->prec = 0;
			k->p = 0;
		}
		k->res = (char *)malloc(sizeof(char) * 2);
		k->res[0] = k->tp;
		k->res[1] = '\0';
		(k->res[0] == '0') ? ft_strclr(k->res) : 0;
	}
	return ;
}
