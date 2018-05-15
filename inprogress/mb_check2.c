/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_check2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:04:32 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 14:04:33 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check if the label exists in the struct (header).
*/

int		mb_label_match(t_lab *lab, char *line)
{
	int i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, line[i]))
		i++;
	while (lab)
	{
		if (ft_strncmp(lab->name, line, i) == 0)
		{
			if (!lab->name[i])
				return (1);
		}
		lab = lab->next;
	}
	return (mb_error2(10));
}

/*
** Check if the directory is correct.
*/

int		mb_directory_check(char **str, int op, int ch)
{
	if (**str == DIRECT_CHAR)
	{
		if (op > 8 && op != 13)
			g_position = g_position + 2;
		else
			g_position = g_position + 4;
		(*str)++;
		if (**str != LABEL_CHAR && !ft_isdigit(**str)/*!(**str >= '0' && **str <= '9')*/ && \
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
			return (mb_sepchar_is_correct(str));
		return (1);
	}
	return (0);
}

/*
** Check if the label exists in the struct (header).
*/

int		mb_label_exists(t_lab *lab, char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != DIRECT_CHAR)
	{
		i++;
		if (line[i] == DIRECT_CHAR)
		{
			i++;
			if (line[i] == LABEL_CHAR)
			{
				i++;
				mb_label_match(lab, &line[i]);
			}
		}
	}
	return (1);
}

/*
** Check if register is correct.
*/

int		mb_check_correct_register(char **str, int ch)
{
	int regist;

	regist = 0;
	if (**str == 'r')
	{
		(*str)++;
		regist = ft_atoi(*str);
		if (regist > REG_NUMBER || regist <= 0)
			return (mb_error2(9));
		(*str)++;
		if (regist > 9)
			(*str)++;
		if (regist > 99)
			(*str)++;
		g_position++;
		if (ch == 1)
			return (mb_sepchar_is_correct(str));
		return (1);
	}
	return (0);
}

/*
** Increment line according to the operation passed. mb_checkline()
*/

int		mb_checkline(char *str)
{
	int		fc;

	fc = mb_oper_name2(str);
	if (fc)
		g_position++;
	if (fc == 1 || fc == 9 || fc == 12 || fc == 14)
		str = str + 4;
	else if (fc == 2 || fc == 3 || fc == 7)
		str = str + 2;
	else if (fc == 15)
		str = str + 5;
	else
		str = str + 3;
	if (fc != 1 && fc != 9 && fc != 12 && fc != 15)
		g_position++;
	mb_check_arguments2(&str, fc);
	while (*str && *str != '\n' && *str != COMMENT_CHAR && *str != ';')
		if (*str && *str != ' ' && *str != '\t' && *str != '\n')
			return (mb_error2(12));
		else
			str++;
		return (1);
}
