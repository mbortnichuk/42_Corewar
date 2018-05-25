/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:04:32 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 03:00:27 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	mb_assign_opcode(int *oct_out, int i, int ch, char *inp_file)
{
	if (ch == 1 && inp_file[i] == 'r')
		*oct_out = 0x40;
	else if (ch == 1 && inp_file[i] == '%')
		*oct_out = 0x80;
	else if (ch == 1)
		*oct_out = 0xC0;
	if (ch == 2 && inp_file[i] == 'r')
		*oct_out = 0x10;
	else if (ch == 2 && inp_file[i] == '%')
		*oct_out = 0x20;
	else if (ch == 2)
		*oct_out = 0x30;
	if (ch == 3 && inp_file[i] == 'r')
		*oct_out = 0x4;
	else if (ch == 3 && inp_file[i] == '%')
		*oct_out = 0x8;
	else if (ch == 3)
		*oct_out = 0xC;
}

int		mb_opcode(int file_descr, int arg, int i, char *inp_file)
{
	int	oct_in;
	int	oct_out;

	oct_in = 0;
	oct_out = 0;
	mb_assign_opcode(&oct_out, i, 1, inp_file);
	oct_in = (oct_in | oct_out);
	if (arg > 1)
	{
		i = mb_move_i(inp_file, i);
		mb_assign_opcode(&oct_out, i, 2, inp_file);
		oct_in = (oct_in | oct_out);
	}
	if (arg > 2)
	{
		i = mb_move_i(inp_file, i);
		mb_assign_opcode(&oct_out, i, 3, inp_file);
		oct_in = (oct_in | oct_out);
	}
	g_temporary++;
	write(file_descr, &oct_in, 1);
	return (1);
}

int		mb_write_direct(int file_descr, int size, t_lab *lab, char **inp_file)
{
	int	length;
	int	i;

	length = 0;
	if (!(i = 0) && **inp_file != DIRECT_CHAR)
		return (0);
	if (++(*inp_file) && **inp_file == LABEL_CHAR && (*inp_file)++)
		i = mb_calc_i(lab, *inp_file);
	else
		i = ft_atoi(*inp_file);
	if (size == 4)
		i = mb_convert_endian(i);
	else
		i = mb_convert_endian2(i);
	write(file_descr, &i, size);
	g_temporary = g_temporary + size;
	mb_move_sepchar(inp_file);
	return (1);
}

int		mb_write_indirect(int file_descr, t_lab *lab, char **inp_file)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	if (**inp_file == LABEL_CHAR && (*inp_file)++)
		i = mb_calc_i(lab, *inp_file);
	else
		i = ft_atoi(*inp_file);
	i = mb_convert_endian2(i);
	write(file_descr, &i, T_IND);
	g_temporary = g_temporary + T_IND;
	mb_move_sepchar(inp_file);
	return (1);
}

int		mb_write_register(int file_descr, char **inp_file)
{
	int	i;

	i = 0;
	if (**inp_file != 'r')
		return (0);
	i = ft_atoi(++(*inp_file));
	write(file_descr, &i, T_REG);
	g_temporary = g_temporary + T_REG;
	mb_move_sepchar(inp_file);
	return (1);
}
