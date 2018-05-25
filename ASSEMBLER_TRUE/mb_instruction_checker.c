/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_instruction_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:04:32 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:06 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check if the SEPARATOR_CHAR is correct.
*/

int		mb_check_sepchar(char **str)
{
	while (**str == '\t' || **str == ' ')
		(*str)++;
	if (**str != SEPARATOR_CHAR)
		return (mb_error(8));
	(*str)++;
	while (**str == '\t' || **str == ' ')
		(*str)++;
	return (1);
}

/*
** Check if the direct is correct.
*/

int		mb_direct_check(int op, int ch, char **str)
{
	if (**str == DIRECT_CHAR)
	{
		if (op > 8 && op != 13)
			g_indx = g_indx + 2;
		else
			g_indx = g_indx + 4;
		(*str)++;
		if (**str != LABEL_CHAR && !(**str >= '0' && **str <= '9') &&
		**str != '-' && **str != '+')
			mb_error2(15);
		if (**str == LABEL_CHAR)
			(*str)++;
		else if (**str == '+' || **str == '-')
			(*str)++;
		while (**str && ft_strchr(LABEL_CHARS, **str))
			(*str)++;
		while (**str == ' ' || **str == '\t')
			(*str)++;
		if (ch == 1)
			return (mb_check_sepchar(str));
		return (1);
	}
	return (0);
}

/*
** Check if the register is correct.
*/

int		mb_register_check(int ch, char **str)
{
	int registr;

	registr = 0;
	if (**str == 'r')
	{
		(*str)++;
		registr = ft_atoi(*str);
		if (registr > REG_NUMBER || registr <= 0)
			return (mb_error(9));
		(*str)++;
		if (registr > 9)
			(*str)++;
		if (registr > 99)
			(*str)++;
		g_indx++;
		if (ch == 1)
			return (mb_check_sepchar(str));
		return (1);
	}
	return (0);
}

/*
** Check if the indirect is correct.
*/

int		mb_indirect_check(int ch, char **str)
{
	if (**str == LABEL_CHAR)
	{
		(*str)++;
		while (**str && ft_strchr(LABEL_CHARS, **str))
			(*str)++;
	}
	else if (((**str == '+' || **str == '-') && (*str)++) ||
	ft_isdigit(**str))
	{
		while (ft_isdigit(**str))
			(*str)++;
	}
	else
		return (0);
	if (**str != '\0' && **str != '\n'
		&& **str != SEPARATOR_CHAR && **str != ' ' && **str != '\t')
		return (mb_error(7));
	g_indx = g_indx + 2;
	if (ch == 1)
		return (mb_check_sepchar(str));
	return (1);
}

/*
** Increment line according to the instruction passed.
*/

int		mb_valid_line_check(char *str)
{
	int	fc;

	fc = mb_instruction_name(str);
	if (fc)
		g_indx++;
	if (fc == 1 || fc == 9 || fc == 12 || fc == 14)
		str = str + 4;
	else if (fc == 2 || fc == 3 || fc == 7)
		str = str + 2;
	else if (fc == 15)
		str = str + 5;
	else
		str = str + 3;
	if (fc != 1 && fc != 9 && fc != 12 & fc != 15)
		g_indx++;
	mb_arg_check(fc, &str);
	while (*str && *str != '\n' && *str != COMMENT_CHAR && *str != ';')
		if (*str && *str != ' ' && *str != '\t' && *str != '\n')
			return (mb_error(12));
		else
			str++;
	return (1);
}
