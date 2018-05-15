/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:42:24 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 13:42:24 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check if file extension is .s
*/

int		mb_check_champion(char *c)
{
	int i;

	i = 0;
	while (c[i])
		i++;
	if (i > 3 && c[i - 1] == 's' && c[i - 2] == '.')
		return (1);
	else
		return (mb_error2(14));
}

/*
** Check if SEPARATOR_CHAR is correct
*/

int		mb_sepchar_is_correct(char **str)
{
	while (**str == '\t' || **str == ' ')
		(*str)++;
	if (**str != SEPARATOR_CHAR)
		return (mb_error2(8));
	(*str)++;
	while (**str == '\t' || **str == ' ')
		(*str)++;
	return (1);
}

/*
** Check if there is a label and it is well formatted.
*/

int		mb_checklabel(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (line[i] == LABEL_CHAR && i > 0)
	{
		i++;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0' || line[i] == COMMENT_CHAR)
			return (1);
		return (2);
	}
	else if (line[i] && line[i] != ' ' && line[i] != '\0' && line[i] != ';' && \
		line[i] != '\n' && line[i] != '\t' && line[i] != COMMENT_CHAR && line[i] != ',')
	{
		if (line[i + 1] == ' ' || line[i + 1] == '\n' || line[i + 1] == '\0')
			return (mb_error1(4));
		return (mb_error1(3));
	}
	return (0);
}

/*
** Check if there is a duplicates in the labels.
*/

int		mb_check_duplicate_label(t_lab *lab)
{
	t_lab	*st;

	st = lab;
	if (!lab)
		return (1);
	lab = lab->next;
	while (lab)
	{
		if (ft_strcmp(st->name, lab->name) == 0)
			return (mb_error2(9));
		lab = lab->next;
	}
	return (mb_check_duplicate_label(st->next));
}

/*
** Check if the indirect is correct.
*/

int		mb_check_indirect(char **str, int ch)
{
	if (**str == LABEL_CHAR)
	{
		(*str)++;
		while (**str && ft_strchr(LABEL_CHARS, **str))
			(*str)++;
	}
	else if (((**str == '+' || **str == '-') && (*str)++) || \
		ft_isdigit(**str))
	{
		while (ft_isdigit(**str))
			(*str)++;
	}
	else
		return (0);
	if (**str != '\0' && **str != '\n' && **str != SEPARATOR_CHAR && \
		**str != ' ' && **str != '\t')
		return (mb_error1(7));
	g_position = g_position + 2;
	if (ch == 1)
		return (mb_sepchar_is_correct(str));
	return (1);
}
