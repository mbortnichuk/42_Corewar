/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:44:27 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/12 17:44:29 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_intbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)) ||
		(c >= 'a' && c <= ('a' + base - 10)));
}

int			ft_atoi_base(const char *str, int str_base)
{
	int		sign;
	int		res;

	res = 0;
	if (str_base <= 1 || str_base > 16)
		return (0);
	while (*str == ' ' || *str == '\n' || *str == '\r' ||
		*str == '\v' || *str == '\t' || *str == '\f')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_intbase(*str, str_base))
	{
		if (*str - 'a' >= 0 && *str - 'a' <= 5)
			res = res * str_base + (*str - 'a' + 10);
		else if (*str - 'A' >= 0 && *str - 'A' <= 5)
			res = res * str_base + (*str - 'A' + 10);
		else
			res = res * str_base + (*str - '0');
		str++;
	}
	return (res * sign);
}
