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

static int			mb_label_match(t_assm *assm, char *line, t_lab_lst *lab)
{
	int	j;

	j = 0;
	while (ft_strchr(LABEL_CHARS, line[j]))
		j++;
	while (lab)
	{
		if (ft_strncmp(lab->data, line, j) == 0)
		{
			if (!lab->data[j])
				return (1);
		}
		lab = lab->next;
	}
	return (error(assm, 10));
}

/*
** Check if the label exists in the struct (header).
*/

static void			cut_comment(char **l)
{
	int			size;
	char		*tmp;

	size = ft_strlen(*l) - ft_strlen(ft_strchr(*l, COMMENT_CHAR));
	tmp = ft_strsub(*l, 0, size);
	ft_strdel(l);
	*l = tmp;
}

int					mb_label_exist(t_assm *assm, char **l)
{
	int			len;
	t_lab_lst	*lab;

	len = 0;
	lab = assm->lab_lst;
	if (!*l)
		return (0);
	ft_strchr(*l, COMMENT_CHAR) ? cut_comment(l) : 0;
	while ((*l)[len] && ((*l)[len] != DIRECT_CHAR || (*l)[len] != LABEL_CHAR))
	{
		len++;
		if ((*l)[len] == DIRECT_CHAR && (*l)[len + 1] == LABEL_CHAR)
		{
			len += 2;
			mb_label_match(assm, &(*l)[len], lab);
		}
		else if ((*l)[len] == LABEL_CHAR && (*l)[len - 1] != DIRECT_CHAR)
		{
			len++;
			mb_label_match(assm, &(*l)[len], lab);
		}
	}
	return (1);
}

/*
** Check if there is a label and if the label_char is well formatted.
*/

int					mb_check_valid_label(t_assm *assm, char *l)
{
	int	j;

	j = 0;
	while (l[j] && (l[j] == ' ' || l[j] == '\t'))
		j++;
	while (l[j] && ft_strchr(LABEL_CHARS, l[j]))
		j++;
	if (l[j] && l[j] == LABEL_CHAR && j > 0)
	{
		j++;
		while (l[j] && (l[j] == ' ' || l[j] == '\t'))
			j++;
		if (l[j] && (l[j] == '\n' || l[j] == '\0' || l[j] == COMMENT_CHAR))
			return (1);
		return (2);
	}
	else if (l[j] && l[j] != ' ' && l[j] != '\0' && l[j] != ';' &&
	l[j] != '\n' && l[j] != '\t' && l[j] != COMMENT_CHAR && l[j] != ',')
	{
		if (l[j + 1] &&
			(l[j + 1] == ' ' || l[j + 1] == '\n' || l[j + 1] == '\0'))
			return (error(assm, 4));
		return (error(assm, 3));
	}
	return (0);
}

/*
** Check if there is a duplicate in the labels.
*/

int					mb_check_label_duplicate(t_assm *assm, t_lab_lst *lab)
{
	t_lab_lst *lst;

	lst = lab;
	if (!lab)
		return (1);
	lab = lab->next;
	while (lab)
	{
		if (!ft_strcmp(lst->data, lab->data))
			return (error(assm, 9));
		lab = lab->next;
	}
	return (mb_check_label_duplicate(assm, lst->next));
}
