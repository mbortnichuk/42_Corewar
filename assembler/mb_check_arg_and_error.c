/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_check_arg_and_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:28:55 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:25:49 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Checks if the instruction name is correct and return
** the corresponding int.
*/

int				io_instruction_name(char *str)
{
	unsigned int	i;

	i = 16;
	while (i > 0)
	{
		if (!strncmp(g_tab[i].name, str, ft_strlen(g_tab[i].name)))
		{
			return (i);
		}
		i--;
	}
	return (0);
}

/*
** Check the validity of the args of each instruct.
*/

static int		mb_arg_check2(t_assm *assm, int op, char **str)
{
	if (op == 3 && mb_reg_check(assm, 1, str) &&
		(mb_ind_check(assm, 0, str) || mb_reg_check(assm, 0, str)))
		return (1);
	if ((op == 4 || op == 5) && mb_reg_check(assm, 1, str) &&
	mb_reg_check(assm, 1, str) && mb_reg_check(assm, 0, str))
		return (1);
	if ((op == 10 || op == 14) && (mb_dir_check(assm, op, 1, str) ||
	mb_reg_check(assm, 1, str) || mb_ind_check(assm, 1, str)) &&
	(mb_dir_check(assm, op, 1, str) || mb_reg_check(assm, 1, str)) &&
	mb_reg_check(assm, 0, str))
		return (1);
	return (error(assm, 8));
}

/*
** Check the validity of the args of each instruct.
*/

int				mb_arg_check(t_assm *assm, int op, char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
	if ((op == 1 || op == 9 || op == 12 || op == 15) &&
	mb_dir_check(assm, op, 0, str))
		return (1);
	if ((op == 2 || op == 13) && (mb_dir_check(assm, op, 1, str) ||
	mb_ind_check(assm, 1, str)) && mb_reg_check(assm, 0, str))
		return (1);
	if ((op == 6 || op == 7 || op == 8) && ((mb_dir_check(assm, op, 1, str) ||
		mb_reg_check(assm, 1, str) || mb_ind_check(assm, 1, str)) &&
		(mb_dir_check(assm, op, 1, str) || mb_reg_check(assm, 1, str)
		|| mb_ind_check(assm, 1, str)) && mb_reg_check(assm, 0, str)))
		return (1);
	if (op == 11 && mb_reg_check(assm, 1, str) &&
		(mb_dir_check(assm, op, 1, str) || mb_reg_check(assm, 1, str) ||
		mb_ind_check(assm, 1, str)) &&
		(mb_dir_check(assm, op, 0, str) || mb_reg_check(assm, 0, str)))
		return (1);
	if (op == 16 && mb_reg_check(assm, 0, str))
		return (1);
	return (mb_arg_check2(assm, op, str));
}

static int		error2(t_assm *assm, int err)
{
	if (err == 11)
		ft_printf("Sorry, can not find name or comment.\n"RC);
	if (err == 12)
		ft_printf("There is no arguments or there are too "
			"much of them for instruction in line: "RED"%d\n"RC, assm->count);
	if (err == 13)
		ft_printf("There is multiple lines of name or comment.\n"RC);
	if (err == 14)
		ft_printf("Incorrect file extension.\n"RC);
	if (err == 15)
		ft_printf("Where is a LABEL_CHAR?\n"RC);
	if (err == 16)
		ft_printf("Can not open/read source file.\n"RC);
	if (err == 17)
		ft_printf("Wrong bot name or comment.\n"RC);
	if (err == 18)
		ft_printf("Empty label in line: "RED"%d\n"RC, assm->count);
	(err >= 16 || err == 14) ? exit(0) : 0;
	return (0);
}

int				error(t_assm *assm, int err)
{
	assm->esc = 1;
	ft_printf(RED"Error: "RC);
	if (err == 1)
		ft_printf("Wrong name format");
	if (err == 2)
		ft_printf("Wrong comment format");
	if (err == 3)
		ft_printf("Wrong LABELS format in line: "RED"%d\n"RC, assm->count);
	if (err == 4)
		ft_printf("Wrong LABEL format in line "RED"%d\n"RC, assm->count);
	if (err == 5)
		ft_printf("Instruct name is wrong in line: "RED"%d\n"RC, assm->count);
	if (err == 7)
		ft_printf("It's not an indirect in line: "RED"%d\n"RC, assm->count);
	if (err == 8)
		ft_printf("Wrong arguments in line "RED"%d\n"RC, assm->count);
	if (err == 9)
		ft_printf("Same label error.\n"RC);
	if (err == 10)
		ft_printf("There is no match between label.\n"RC);
	return (error2(assm, err));
}
