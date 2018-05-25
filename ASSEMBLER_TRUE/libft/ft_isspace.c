/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:06:20 by iosypenk          #+#    #+#             */
/*   Updated: 2017/12/08 18:06:28 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if ((c == '\r') || (c == '\v') || (c == '\t') ||
		(c == '\f') || (c == '\n') || (c == ' '))
		return (1);
	return (0);
}
