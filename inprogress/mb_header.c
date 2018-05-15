/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_header.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:29:34 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 14:29:35 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Move the pointer just before name or comment.
*/

int		mb_move_header(char *str, int name, int comment, int ch)
{
	int i;

	if (ch)
		i = name;
	else
		i = comment;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '"')
		return (0);
	i++;
	return (i);
}

int		mb_move_header_end(char *str, int i)
{
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] == '"')
		i++;
	while (str[i] && str[i] != '\n' && i++)
		if (str[i] && str[i] != ' ' && str[i] != '\t')
			return (mb_error1(1));
		return (0);
}

/*
** Retrieve the name and store it in the struct (header).
*/

int		mb_handle_name_comm(int file_descr, t_header *header)
{
	char	*str;
	int i;

	i = 0;
	str = 0;
	while (get_next_line(file_descr, &str) > 0)
	{
		g_str++;
		if (str[0] != COMMENT_CHAR && str[0] != ';' && str[0] != '\0')
		{
			while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
				i++;
			mb_name_comm_cpy(&str[i], header, ft_strlen(NAME_CMD_STRING), ft_strlen(COMMENT_CMD_STRING));
			if (mb_return_header(header, str) == 1)
				return (1);
		}
		free(str);
		str = NULL;
	}
	return (mb_error2(11));
}
