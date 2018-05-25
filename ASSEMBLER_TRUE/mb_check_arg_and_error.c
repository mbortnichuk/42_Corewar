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
** Check the validity of the args of each instruct.
*/

int		mb_arg_check2(int op, char **str)
{
	if (op == 3 && mb_register_check(1, str) && (mb_indirect_check(0, str) ||
	mb_register_check(0, str)))
		return (1);
	if ((op == 4 || op == 5) && mb_register_check(1, str) &&
	mb_register_check(1, str) && mb_register_check(0, str))
		return (1);
	if ((op == 10 || op == 14) && (mb_direct_check(op, 1, str) ||
	mb_register_check(1, str) || mb_indirect_check(1, str)) &&
	(mb_direct_check(op, 1, str) || mb_register_check(1, str)) &&
	mb_register_check(0, str))
		return (1);
	return (mb_error(8));
}

/*
** Check the validity of the args of each instruct.
*/

int		mb_arg_check(int op, char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
	if ((op == 1 || op == 9 || op == 12 || op == 15) &&
	mb_direct_check(op, 0, str))
		return (1);
	if ((op == 2 || op == 13) && (mb_direct_check(op, 1, str) ||
	mb_indirect_check(1, str)) && mb_register_check(0, str))
		return (1);
	if ((op == 6 || op == 7 || op == 8) && ((mb_direct_check(op, 1, str) ||
	mb_register_check(1, str) || mb_indirect_check(1, str))
	&& (mb_direct_check(op, 1, str) || mb_register_check(1, str) ||
	mb_indirect_check(1, str)) && mb_register_check(0, str)))
		return (1);
	if (op == 11 && mb_register_check(1, str) && (mb_direct_check(op, 1, str) ||
	mb_register_check(1, str) || mb_indirect_check(1, str)) &&
	(mb_direct_check(op, 0, str) || mb_register_check(0, str)))
		return (1);
	if (op == 16 && mb_register_check(0, str))
		return (1);
	return (mb_arg_check2(op, str));
}

int		mb_error2(int err)
{
	if (err == 11)
		ft_printf(RED BOLD"Sorry, cannot find name or comment.\n"RC);
	if (err == 12)
		ft_printf(RED BOLD"There is no arguments or there are too much of them for instruction in line: %d\n"RC,
		g_str); 
	if (err == 13)
		ft_printf(RED BOLD"There is multiple lines of name or comment.\n"RC);
	if (err == 14)
		ft_printf(RED BOLD"Incorrect file extension, bro.\n"RC);
	if (err == 15)
		ft_printf(RED BOLD"Where is a LABEL_CHAR?\n"RC);
	exit(0);
	return (0);
}

int		mb_error(int err)
{
	if (err == 1)
		ft_printf(RED BOLD"Name format is wrong in line: %d\n"RC, g_str);
	if (err == 2)
		ft_printf(RED BOLD"Comment format is wrong in line -> line: %d\n"RC, g_str);
	if (err == 3)
		ft_printf(RED BOLD"LABELS_CHAR format is wrong in line: %d\n"RC, g_str);
	if (err == 4)
		ft_printf(RED BOLD"LABEL_CHAR format is wrong in line %d\n"RC, g_str);
	if (err == 5)
		ft_printf(RED BOLD"Instruct name is wrong in line: %d\n"RC, g_str);
	if (err == 7)
		ft_printf(RED BOLD"It's not an indirect in line: %d\n"RC, g_str);
	if (err == 8)
		ft_printf(RED BOLD"Something went wrong with arguments, bro: %d\n"RC, g_str);
	if (err == 9)
		ft_printf(RED BOLD"Same label error.\n"RC);
	if (err == 10)
		ft_printf(RED BOLD"There is no match between label.\n"RC);
	return (mb_error2(err));
}
