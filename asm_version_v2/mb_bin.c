/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 08:56:40 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 08:56:42 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	mb_rev_32byte(unsigned int n)
{
	unsigned int	rev;

	rev = 0x000000FF & n;
	rev = (rev << 8) + ((0x0000FF00 & n) >> 8);
	rev = (rev << 8) + ((0x00FF0000 & n) >> 16);
	rev = (rev << 8) + ((0xFF000000 & n) >> 24);
	return (rev);
}

unsigned short	mb_rev_16byte(unsigned int n)
{
	unsigned short	rev;

	rev = 0x00FF & n;
	rev = (rev << 8) + ((0xFF00 & n) >> 8);
	return (rev);
}

unsigned int	mb_read_fix32(int area)
{
	unsigned int	arg_i;

	read(area, &arg_i, 4);
	return (mb_rev_32byte(arg_i));
}

unsigned int	mb_read_fix16(int area)
{
	unsigned short	arg_s;

	read(area, &arg_s, 2);
	return (mb_rev_16byte(arg_s));
}

ssize_t	mb_fix_write(int area, const void *buff, size_t nbt) // nbt -> nbyte
{
	unsigned int	fix;

	if (nbt == 4)
		fix = mb_rev_32byte(*(unsigned int *)buff);
	else if (nbt == 2)
		fix = mb_rev_16byte(*(unsigned int *)buff);
	else
		fix = *(unsigned int *)buff;
	return (write(area, &fix, nbt));
}
