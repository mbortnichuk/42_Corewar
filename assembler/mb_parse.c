/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_start_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:02:26 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:30 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check is the file ends with .s
*/

int					mb_champion_check(t_assm *assm, char *champion)
{
	int		j;

	j = 0;
	while (champion[j])
		j++;
	if (j > 3 && champion[j - 1] == 's' && champion[j - 2] == '.')
		return (1);
	else
		return (error(assm, 14));
}

/*
** Return 1 if header is ok, if not ok - 0 and then error.
*/

static char			*mb_realloc(char *inp_file, char *str, int i)
{
	char	*sub_str;
	char	*temporary;
	int		length;

	length = 0;
	temporary = NULL;
	sub_str = NULL;
	sub_str = ft_strsub(str, i, ft_strlen(str));
	temporary = ft_strnew(ft_strlen(inp_file) + ft_strlen(sub_str) + 1);
	temporary = ft_strcpy(temporary, inp_file);
	temporary = ft_strcat(temporary, sub_str);
	ft_strdel(&inp_file);
	ft_strdel(&sub_str);
	while (temporary[length])
		length++;
	temporary[length] = '\n';
	inp_file = ft_strdup(temporary);
	free(temporary);
	return (inp_file);
}

/*
** Function that realloc to retrieve the entire .s file.
*/

static char			*mb_join_free(char *inp_file, char *str)
{
	char	*sub_str;
	int		length;
	int		i;

	i = 0;
	sub_str = NULL;
	if (str[i])
	{
		if (!inp_file)
		{
			length = 0;
			sub_str = ft_strsub(str, i, ft_strlen(str) - i);
			inp_file = ft_strnew((ft_strlen(sub_str) + 1));
			inp_file = ft_strcpy(inp_file, sub_str);
			while (inp_file[length])
				length++;
			inp_file[length] = '\n';
			ft_strdel(&sub_str);
		}
		else
		{
			inp_file = mb_realloc(inp_file, str, i);
		}
	}
	return (inp_file);
}

/*
** Put the valid line in array.
*/

static char			*save_line(t_assm *assm, char *str, char *inp_file, int i)
{
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	if (str[i] && str[i] != COMMENT_CHAR && str[i] != ';' &&
	mb_valid_line_check(assm, &str[i]))
		inp_file = mb_join_free(inp_file, &str[i]);
	ft_strdel(&str);
	return (inp_file);
}

/*
** Retrieve the name of the label, position in a chained list.
*/

void				mb_parse_str(t_assm *assm, char **inp_file)
{
	int		i;
	char	*str;
	int		len;

	str = NULL;
	while (get_next_line(assm->fd_s, &str) > 0)
	{
		i = 0;
		assm->count++;
		while (str[i] && (str[i] == '\t' || str[i] == ' '))
			i++;
		if (str[i] && str[i] != COMMENT_CHAR && str[i] != ';' &&
			mb_check_valid_label(assm, str) >= 1)
		{
			len = 0;
			while (str[len] && str[len] != LABEL_CHAR)
				len++;
			io_create_lab_lst(&assm->lab_lst, ft_strsub(str, 0, len));
			while (str[i] && str[i] != LABEL_CHAR)
				i++;
			i++;
		}
		if (str != NULL)
			*inp_file = save_line(assm, str, *inp_file, i);
	}
}
