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

static int		mb_check_sepchar(t_assm *assm, char **str)
{
	while (**str == '\t' || **str == ' ')
		(*str)++;
	if (**str != SEPARATOR_CHAR)
		return (error(assm, 8));
	(*str)++;
	while (**str == '\t' || **str == ' ')
		(*str)++;
	return (1);
}

/*
** Check if the direct is correct.
*/

int				mb_dir_check(t_assm *assm, int op, int ch, char **str)
{
	if (**str == DIRECT_CHAR)
	{
		if (op > 8 && op != 13)
			assm->args_count += 2;
		else
			assm->args_count += 4;
		(*str)++;
		if (**str != LABEL_CHAR && !(**str >= '0' && **str <= '9') &&
		**str != '-' && **str != '+')
			error(assm, 15);
		if (**str == LABEL_CHAR)
			(*str)++;
		else if (**str == '+' || **str == '-')
			(*str)++;
		while (**str && ft_strchr(LABEL_CHARS, **str))
			(*str)++;
		while (**str == ' ' || **str == '\t')
			(*str)++;
		if (ch == 1)
			return (mb_check_sepchar(assm, str));
		return (1);
	}
	return (0);
}

/*
** Check if the register is correct.
*/

int				mb_reg_check(t_assm *assm, int ch, char **str)
{
	int registr;

	registr = 0;
	if (**str == 'r')
	{
		(*str)++;
		registr = ft_atoi(*str);
		if (registr > REG_NUMBER || registr <= 0)
			return (error(assm, 9));
		(*str)++;
		if (registr > 9)
			(*str)++;
		if (registr > 99)
			(*str)++;
		assm->args_count++;
		if (ch == 1)
			return (mb_check_sepchar(assm, str));
		return (1);
	}
	return (0);
}

/*
** Check if the indirect is correct.
*/

int				mb_ind_check(t_assm *assm, int ch, char **str)
{
	if (**str == LABEL_CHAR)
	{
		(*str)++;
		while (**str && ft_strchr(LABEL_CHARS, **str))
			(*str)++;
	}
	else if (((**str == '+' || **str == '-') && (*str)++) || ft_isdigit(**str))
	{
		while (ft_isdigit(**str))
			(*str)++;
	}
	else
		return (0);
	if (**str != '\0' && **str != '\n'
		&& **str != SEPARATOR_CHAR && **str != ' ' && **str != '\t')
		return (error(assm, 7));
	assm->args_count += 2;
	if (ch == 1)
		return (mb_check_sepchar(assm, str));
	return (1);
}

/*
** Increment line according to the instruction passed.
*/

int				mb_valid_line_check(t_assm *assm, char *str)
{
	int	fc;

	fc = io_instruction_name(str);
	if (fc)
		assm->args_count++;
	if (fc == 1 || fc == 9 || fc == 12 || fc == 14)
		str = str + 4;
	else if (fc == 2 || fc == 3 || fc == 7)
		str = str + 2;
	else if (fc == 15)
		str = str + 5;
	else
		str = str + 3;
	if (fc != 1 && fc != 9 && fc != 12 & fc != 15)
		assm->args_count++;
	mb_arg_check(assm, fc, &str);
	while (*str && *str != '\n' && *str != COMMENT_CHAR && *str != ';')
		if (*str && *str != ' ' && *str != '\t' && *str != '\n')
			return (error(assm, 12));
		else
			str++;
	return (1);
}
