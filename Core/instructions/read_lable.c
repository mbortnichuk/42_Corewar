/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrybak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:38:11 by mrybak            #+#    #+#             */
/*   Updated: 2018/05/03 13:38:14 by mrybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../corewar.h"

int				four_byte(unsigned char *map, unsigned int adr)
{
	int	res;

	res = (*(map + adr % MEM_SIZE) << 24 | *(map + (adr + 1) % MEM_SIZE) << 16 |
			*(map + (adr + 2) % MEM_SIZE) << 8 | *(map + (adr + 3) % MEM_SIZE));
	return (res);
}

short int		two_byte(unsigned char *map, unsigned int adr)
{
	short int	res;

	res = (*(map + adr % MEM_SIZE) << 8 | *(map + (adr + 1) % MEM_SIZE));
	return (res);
}

unsigned int	read_direct(t_core *core, int pos, char label_size)
{
	unsigned int		value;

	value = 0;
	if (label_size == 0)
	{
		value = four_byte(core->map, pos);
	}
	else if (label_size == 1)
	{
		value = two_byte(core->map, pos);
	}
	return (value);
}

void			write_to_map(unsigned char map[MEM_SIZE],
								unsigned int value, int adr)
{
	map[adr % MEM_SIZE] = value >> 24 & 255;
	map[(adr + 1) % MEM_SIZE] = value >> 16 & 255;
	map[(adr + 2) % MEM_SIZE] = value >> 8 & 255;
	map[(adr + 3) % MEM_SIZE] = value & 255;
}
