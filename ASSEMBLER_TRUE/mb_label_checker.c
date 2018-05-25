/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_label_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:29:34 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:21 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check if the label exists in the struct (header).
*/

static int		mb_label_match(char *line, t_lab *lab)
{
	int	j;

	j = 0;
	while (ft_strchr(LABEL_CHARS, line[j]))
		j++;
	while (lab)
	{
		if (ft_strncmp(lab->name, line, j) == 0)
		{
			if (!lab->name[j])
				return (1);
		}
		lab = lab->next;
	}
	return (mb_error(10)); //SHO TUT, PODUVUTUS'
}

/*
** Check if the label exists in the struct (header).
*/

int		mb_label_exist(char *line, t_lab *lab)
{
	int length;

	length = 0;
	if (!line)
		return (0);
	while (line[length] && line[length] != DIRECT_CHAR)
	{
		length++;
		if (line[length] == DIRECT_CHAR)
		{
			length++;
			if (line[length] == LABEL_CHAR)
			{
				length++;
				mb_label_match(&line[length], lab);
			}
		}
	}
	return (1);
}

/*
** Check if there is a label and if the label_char is well formatted.
*/

int		mb_check_valid_label(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	while (line[j] && ft_strchr(LABEL_CHARS, line[j]))
		j++;
	if (line[j] == LABEL_CHAR && j > 0)
	{
		j++;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (line[j] == '\n' || line[j] == '\0' || line[j] == COMMENT_CHAR)
			return (1);
		return (2);
	}
	else if (line[j] && line[j] != ' ' && line[j] != '\0' && line[j] != ';' &&
	line[j] != '\n' && line[j] != '\t' && line[j] != COMMENT_CHAR && line[j] != ',')
	{
		if (line[j + 1] == ' ' || line[j + 1] == '\n' || line[j + 1] == '\0')
			return (mb_error(4));
		return (mb_error(3));
	}
	return (0);
}

/*
** Check if there is a duplicate in the labels.
*/

int		mb_check_label_duplicate(t_lab *lab)
{
	t_lab *start_point;

	start_point = lab;
	if (!lab)
		return (1);
	lab = lab->next;
	while (lab)
	{
		if (ft_strcmp(start_point->name, lab->name) == 0)
			return (mb_error(9));
		lab = lab->next;
	}
	return (mb_check_label_duplicate(start_point->next));
}
