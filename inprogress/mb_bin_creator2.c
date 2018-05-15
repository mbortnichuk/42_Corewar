/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_bim_creator2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:11:30 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 16:11:31 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_convert_endian1(int i)
{
	i = ((i >> 24) & 0xff) | ((i >> 8) & 0xff00) | ((i << 8) & 0xff0000) | \
		((i << 24) & 0xff000000);
		return (i);
}

int		mb_convert_endian2(int i)
{
	i = ((i >> 8) & 0xff) | ((i << 8) & 0xff00);
	return (i);
}

void	mb_set_opcode(int *oct, int i, int ch, char *f)
{
	if (ch == 1 && f[i] == 'r')
		*oct = 0x40;
	else if (ch == 1 && f[i] == '%')
		*oct = 0x80;
	else if (ch == 1)
		*oct = 0xC0;
	if (ch == 2 && f[i] == 'r')
		*oct = 0x10;
	else if (ch == 2 && f[i] == '%')
		*oct = 0x20;
	else if (ch == 2)
		*oct = 0x30;
	if (ch == 3 && f[i] == 'r')
		*oct = 0x4;
	else if (ch == 3 && f[i] == '%')
		*oct = 0x8;
	else if (ch == 3)
		*oct = 0xC;
}

int		mb_move_i(int i, char *f)
{
	while (f[i] != ',')
		i++;
	i++;
	while (f[i] == '\t' || f[i] == ' ')
		i++;
	return (i);
}

int		mb_calc_i(char *f, t_lab *lab)
{
	size_t	length;

	length = 0;
	while (ft_strchr(LABEL_CHARS, f[length]))
		length++;
	while (lab)
	{
		if (length >= ft_strlen(lab->name))
		{
			if (!ft_strncmp(f, lab->name, length))
				return (lab->position - g_position);
		}
		else if (!ft_strncmp(f, lab->name, ft_strlen(lab->name)))
			return (lab->position - g_position);
		lab = lab->next;
	}
	return (mb_error2(12));
}
