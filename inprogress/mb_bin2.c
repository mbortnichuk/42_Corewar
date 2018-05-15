/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_bin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:19:04 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 20:19:06 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_scary_func_name1(int fc, int file_descr, t_lab *lab, char **f)
{
	if ((fc == 6 || fc == 7 || fc == 8) && mb_opcode(file_descr, 3, 0, *f) && \
		((mb_put_register(file_descr, f) || mb_put_directory(file_descr, 4, lab, f) || \
			mb_put_indirect(file_descr, lab, f)) && ((mb_put_register(file_descr, f) || \
				mb_put_directory(file_descr, 4, lab, f) || mb_put_indirect(file_descr, lab, f)))))
		return (mb_put_register(file_descr, f));
	else if (fc == 9 || fc == 12 || fc == 15)
		return (mb_put_directory(file_descr, 2, lab, f));
	else if ((fc == 10 || fc == 14) && mb_opcode(file_descr, 3, 0, *f) && \
		(((mb_put_register(file_descr, f) || mb_put_directory(file_descr, 2, lab, f) || \
			mb_put_indirect(file_descr, lab, f)) && (mb_put_register(file_descr, f) || \
			mb_put_directory(file_descr, 2, lab, f)))))
		return (mb_put_register(file_descr, f));
	else if (fc == 11 && mb_opcode(file_descr, 3, 0, *f) && ((mb_put_register(file_descr, f) && \
		(mb_put_register(file_descr, f) || mb_put_directory(file_descr, 2, lab, f) || \
			mb_put_indirect(file_descr, lab, f)) && (mb_put_register(file_descr, f) || \
			mb_put_directory(file_descr, 2, lab, f)))))
		return (1);
	else if (fc == 16 && write(file_descr, "@", 1) && ++g_temporary)
		return (mb_put_register(file_descr, f));
	return (1);
}

int		mb_scary_func_name2(int fc, int file_descr, t_lab *lab, char **f)
{
	*f = mb_filemove(fc, *f);
	write(file_descr, &fc, 1);
	if (fc == 1)
		return (mb_put_directory(file_descr, 4, lab, f));
	else if ((fc == 2 || fc == 13) && mb_opcode(file_descr, 2, 0, *f) && \
		((mb_put_directory(file_descr, 4, lab, f) || mb_put_indirect(file_descr, lab, f))))
		return (mb_put_register(file_descr, f));
	else if (fc == 3 && mb_opcode(file_descr, 2, 0, *f) && mb_put_register(file_descr, f) && \
		(mb_put_register(file_descr, f) || mb_put_indirect(file_descr, lab, f)))
		return (1);
	else if ((fc == 4 || fc == 5) && write(file_descr, "T", 1) && ++g_temporary && \
		mb_put_register(file_descr, f) && mb_put_register(file_descr, f) && \
		mb_put_register(file_descr, f))
		return (1);
	return (mb_scary_func_name1(fc, file_descr, lab, f));
}
