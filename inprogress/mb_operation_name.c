/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_operation_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:44:27 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 11:44:28 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check if the operation name is correct and return the corresponding int.
*/

int		mb_oper_name1(char *str)
{
	if (ft_strncmp("live", str, 4) == 0)
		return (1);
	else if (ft_strncmp("ld", str, 2) == 0)
		return (2);
	else if (ft_strncmp("st", str, 2) == 0)
		return (3);
	else if (ft_strncmp("add", str, 3) == 0)
		return(4);
	else if (ft_strncmp("sub", str, 3) == 0)
		return (5);
	else if (ft_strncmp("and", str, 3) == 0)
		return (6);
	else if (ft_strncmp("or", str, 2) == 0)
		return (7);
	else if (ft_strncmp("xor", str, 3) == 0)
		return (8);
	else if (ft_strncmp("zjmp", str, 4) == 0)
		return (9);
	else if (ft_strncmp("ldi", str, 3) == 0)
		return (10);
	return (0);
}

int		mb_oper_name2(char *str)
{
	if (ft_strncmp("sti", str, 3) == 0)
		return (11);
	else if (ft_strncmp("fork", str, 4) == 0)
		return (12);
	else if (ft_strncmp("lld", str, 3) == 0)
		return (13);
	else if (ft_strncmp("lldi", str, 4) == 0)
		return (14);
	else if (ft_strncmp("lfork", str, 5) == 0)
		return (15);
	else if (ft_strncmp("aff", str, 3) == 0)
		return (16);
	return (mb_oper_name1(str));
}

/*
**  Error output.
*/

int		mb_error1(int er)
{
	if (er == 1)
		ft_printf(RED BOLD"Incorrect name format in line: %d\n"RC, g_str);
	else if (er == 2)
		ft_printf(RED BOLD"Incorrect comment format in line: %d\n"RC, g_str);
	else if (er == 3)
		ft_printf(RED BOLD"Incorrect labels_char format in line: %d\n"RC, g_str);
	else if (er == 4)
		ft_printf(RED BOLD"Incorrect label_char format in line: %d\n"RC, g_str);
	else if (er == 5)
		ft_printf(RED BOLD"Incorrect operation name in line: %d\n"RC, g_str);
	else if (er == 7)
		ft_printf(RED BOLD"It is not an indirect in line: %d\n"RC, g_str);
	exit(0);
	return (0);
}

int		mb_error2(int er)
{
	if (er == 8)
		ft_printf(RED BOLD"There is some issues with program arguments. %d\n"RC, g_str);
	else if (er == 9)
		ft_printf(RED BOLD"There is the same label being used.\n"RC);
	else if (er == 10)
		ft_printf(RED BOLD"There is no matching between labels.\n"RC);
	else if (er == 11)
		ft_printf(RED BOLD"Cannot find name or comment.\n"RC);
	else if (er == 12)
		ft_printf(RED BOLD"Cannot find any arguments or there are too much of them: %d\n"RC);
	else if (er == 13)
		ft_printf(RED BOLD"There are multiple lines of name or comment.\n"RC);
	else if (er == 14)
		ft_printf(RED BOLD"Incorrect file extension.\n"RC);
	else if (er == 15)
		ft_printf(RED BOLD"Where is LABEL_CHAR?\n"RC);
	return (mb_error1(er));
}
