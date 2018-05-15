/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bS.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:50:33 by iosypenk          #+#    #+#             */
/*   Updated: 2018/01/15 12:50:39 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_to_res(char *str, char symb)
{
	size_t	len;
	char	*res;
	int		i;

	len = ft_strlen(str) + 1;
	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = 0;
	res[len - 1] = symb;
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	free(str);
	return (res);
}

void	one(t_type *k, int *n, int tmp)
{
	tmp = *n;
	k->res = add_to_res(k->res, (char)tmp);
}

void	two(t_type *k, int *n, int tmp)
{
	tmp = *n >> 6;
	tmp |= 192;
	k->res = add_to_res(k->res, (char)tmp);
	tmp = *n;
	tmp &= 63;
	tmp |= 128;
	k->res = add_to_res(k->res, (char)tmp);
}

void	three(t_type *k, int *n, int tmp)
{
	tmp = *n >> 6 * 2;
	tmp |= 224;
	k->res = add_to_res(k->res, (char)tmp);
	tmp = *n >> 6;
	tmp &= 63;
	tmp |= 128;
	k->res = add_to_res(k->res, (char)tmp);
	tmp = *n;
	tmp &= 63;
	tmp |= 128;
	k->res = add_to_res(k->res, (char)tmp);
}

void	four(t_type *k, int *n, int tmp)
{
	tmp = *n >> 6 * 3;
	tmp |= 240;
	k->res = add_to_res(k->res, (char)tmp);
	tmp = *n >> 6 * 2;
	tmp &= 63;
	tmp |= 128;
	k->res = add_to_res(k->res, (char)tmp);
	tmp = *n >> 6;
	tmp &= 63;
	tmp |= 128;
	k->res = add_to_res(k->res, (char)tmp);
	tmp = *n;
	tmp &= 63;
	tmp |= 128;
	k->res = add_to_res(k->res, (char)tmp);
}
