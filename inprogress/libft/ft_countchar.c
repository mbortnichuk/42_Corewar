/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:43:24 by iosypenk          #+#    #+#             */
/*   Updated: 2017/11/10 11:43:29 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_countchar(const char *str, char c)
{
	int		len;

	len = 0;
	while (*str == c)
		str++;
	while (*str)
	{
		if (*str != c)
		{
			len++;
			str++;
		}
		else
			str++;
	}
	return (len);
}
