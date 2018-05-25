/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_binary_writer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:37:39 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 02:59:10 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*asm_move_file(int fc, char *inp_file)
{
	if (fc == 1 || fc == 9 || fc == 12 || fc == 14)
		inp_file = inp_file + 4;
	else if (fc == 2 || fc == 3 || fc == 7)
		inp_file = inp_file + 2;
	else if (fc == 15)
		inp_file = inp_file + 5;
	else
		inp_file = inp_file + 3;
	while (*inp_file && (*inp_file == ' ' || *inp_file == '\t'))
		inp_file++;
	return (inp_file);
}

int		mb_move_sepchar(char **inp_file)
{
	while (**inp_file && **inp_file != SEPARATOR_CHAR && **inp_file != '\n')
		(*inp_file)++;
	if (**inp_file == '\n')
		return (1);
	(*inp_file)++;
	while (**inp_file && (**inp_file == ' ' || **inp_file == '\t'))
		(*inp_file)++;
	return (1);
}

int		mb_scary_func_name2(int fct, int fd, t_lab *label, char **file)
{
	if ((fct == 6 || fct == 7 || fct == 8) && mb_opcode(fd, 3, 0, *file)
		&& ((mb_write_register(fd, file) || mb_write_direct(fd, 4, label, file) ||
		mb_write_indirect(fd, label, file)) &&
		((mb_write_register(fd, file) || mb_write_direct(fd, 4, label, file) ||
		mb_write_indirect(fd, label, file)))))
		return (mb_write_register(fd, file));
	else if (fct == 9 || fct == 12 || fct == 15)
		return (mb_write_direct(fd, 2, label, file));
	else if ((fct == 10 || fct == 14) && mb_opcode(fd, 3, 0, *file) &&
		(((mb_write_register(fd, file) || mb_write_direct(fd, 2, label, file) ||
		mb_write_indirect(fd, label, file)) &&
		(mb_write_register(fd, file) || mb_write_direct(fd, 2, label, file)))))
		return (mb_write_register(fd, file));
	else if (fct == 11 && mb_opcode(fd, 3, 0, *file) &&
		((mb_write_register(fd, file) && (mb_write_register(fd, file) ||
		mb_write_direct(fd, 2, label, file) || mb_write_indirect(fd, label, file)) &&
		(mb_write_register(fd, file) || mb_write_direct(fd, 2, label, file)))))
		return (1);
	else if (fct == 16 && write(fd, "@", 1) && ++g_temporary)
		return (mb_write_register(fd, file));
	return (1);
}

int		mb_scary_func_name(int fct, int fd, t_lab *label, char **file)
{
	*file = asm_move_file(fct, *file);
	write(fd, &fct, 1);
	if (fct == 1)
		return (mb_write_direct(fd, 4, label, file));
	else if ((fct == 2 || fct == 13) && mb_opcode(fd, 2, 0, *file) &&
		((mb_write_direct(fd, 4, label, file) || mb_write_indirect(fd, label, file))))
		return (mb_write_register(fd, file));
	else if (fct == 3 && mb_opcode(fd, 2, 0, *file) && mb_write_register(fd, file)
		&& (mb_write_register(fd, file) || mb_write_indirect(fd, label, file)))
		return (1);
	else if ((fct == 4 || fct == 5) && write(fd, "T", 1) && ++g_temporary &&
		mb_write_register(fd, file) && mb_write_register(fd, file) &&
		mb_write_register(fd, file))
		return (1);
	return (mb_scary_func_name2(fct, fd, label, file));
}

int		mb_create_bin(int file_descr, t_lab *lab, char *inp_file)
{
	int fc;

	fc = 0;
	while (*inp_file)
	{
		fc = mb_instruction_name(inp_file);
		if (fc)
			g_temporary++;
		mb_scary_func_name(fc, file_descr, lab, &inp_file);
		while (*inp_file && *inp_file != '\n')
			inp_file++;
		inp_file++;
		g_indx = g_indx + g_temporary;
		g_temporary = 0;
	}
	return (1);
}
