/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_header_cpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:00:52 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:25:58 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Move the pointer just before the name or comment.
*/

static int			mb_head_pass(int n, int c, int ch, char *str)
{
	int	j;

	if (ch)
		j = n;
	else
		j = c;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	if (str[j] != '"')
		return (0);
	j++;
	ft_printf("|%s|\n", str);
	return (j);
}

static int			mb_head_end_pass(int j, char *str)
{
	while (str[j] && str[j] != '"')
		j++;
	if (str[j] == '"')
		j++;
	while (str[j] && str[j] != '\n' && j++)
		if (str[j] && str[j] != ' ' && str[j] != '\t')
			return (mb_error(1));
	return (0);
}

/*
** Get the name and the comment and store it in the struct(header).
*/

static t_header	*mb_copy_head(t_header *header, char *str, int ch)
{
	char *temporary;

	temporary = NULL;
	if (ch == 0)
	{
		temporary = ft_strsub(str, 0, ft_strclen('"', str));
		ft_strncat(header->prog_name, temporary, PROG_NAME_LENGTH);
	}
	if (ch == 1)
	{
		if (str[0] == '"')
			ft_strcpy(header->comment, "I do not need a champ tp defeat you ;)");
		else
		{
			temporary = ft_strsub(str, 0, ft_strclen('"', str));
			ft_strncat(header->comment, temporary, COMMENT_LENGTH);
		}
	}
	if (temporary != NULL)
		free(temporary);
	temporary = NULL;
	return (header);
}

static int			mb_name_comm_copy(t_header *header, char *str, int n, int c)
{
	char	*temporary;
	int		i;

	i = 0;
	temporary = NULL;
	if (!header->prog_name[0] && ft_strncmp(NAME_CMD_STRING, str, n) == 0)
	{
		if ((i = mb_head_pass(n, c, 1, str)) == 0)
			return (mb_error(1));
		else
		{
			mb_copy_head(header, &str[i], 0);
			ft_printf(YEL"111 %s\n"RC, header->prog_name);
		}
	}
	else if (!header->comment[0] &&
		ft_strncmp(COMMENT_CMD_STRING, str, c) == 0)
	{
		if ((i = mb_head_pass(n, c, 0, str)) == 0)
			return (mb_error(11));
		else
		{
			header = mb_copy_head(header, &str[i], 1);
			// ft_printf(RED BOLD"sraka: | %s |\n"RC, header);
		}
	}
	else
		return (mb_error(11));
	ft_printf(YEL"gde ja: %s\n"RC, str);
	return (mb_head_end_pass(i, str));
}

/*
** Get the name and the comment and store it in the struct(header).
*/

int			mb_handle_name_comm(t_header *header, int file_descr)
{
	char	*str;
	int		i;

	i = 0;
	str = 0;
	while (get_next_line(file_descr, &str) > 0)
	{
		g_str++;
		if (str[0] != COMMENT_CHAR && str[0] != ';' && str[0] != '\0')
		{
			while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
				i++;
			// ft_printf(CYN"line: | %s |\n"RC, str);
			mb_name_comm_copy(header, &str[i], ft_strlen(NAME_CMD_STRING),
			ft_strlen(COMMENT_CMD_STRING));
			ft_printf(MAG"header: | %s |\n"RC, header->comment);
			ft_printf(CYN"shto eto: | %s |\n"RC, header->comment);
			if (mb_return_header(str, header) == 1)
				return (1);
		}
		free(str);
		str = NULL;
	}
	return (mb_error(11));
}
