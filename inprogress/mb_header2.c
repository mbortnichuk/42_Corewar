/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_header2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:00:52 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 10:00:53 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Return 1 if header is complete, if not complete - return 0 or then error.
*/

int		mb_return_header(t_header *header, char *str)
{
	if (header->comment[0] && header->prog_name[0])
	{
		if (ft_strrchr(str, '"') != ft_strrchr(str, '"'))
		{
			free(str);
			str = NULL;
			return (1);
		}
		return (mb_error2(13));
	}
	return (0);
}

t_header	*mb_header_cpy(char *str, t_header *header, int ch)
{
	char	*temp;

	temp = NULL;
	if (ch == 0)
	{
		temp = ft_strsub(str, 0, ft_strclen(str, '"'));
		ft_strncat(header->prog_name, temp, PROG_NAME_LENGTH);
	}
	if (ch == 1)
	{
		if (str[0] == '"')
			ft_strcpy(header->comment, "I don't need any comments to defeat you ;)");
		else
		{
			temp = ft_strsub(str, 0, ft_strclen(str, '"'));
			ft_strncat(header->comment, temp, COMMENT_LENGTH);
		}
	}
	if (temp != NULL)
		free(temp);
	temp = NULL;
	return (header);
}

int		mb_name_comm_cpy(char *str, t_header *header, int n, int c)
{
	char	*temp;
	int i;

	i = 0;
	temp = NULL;
	if (!header->prog_name[0] && ft_strncmp(NAME_CMD_STRING, str, n) == 0)
	{
		if ((i = mb_move_header(str, n, c, 1)) == 0)
			return (mb_error1(1));
		else
			mb_header_cpy(&str[i], header, 0);
	}
	else if (!header->comment[0] && ft_strncmp(COMMENT_CMD_STRING, str, c) == 0)
	{
		if ((i = mb_move_header(str, n, c, 0)) == 0)
			return (mb_error2(11));
		else
			header = mb_header_cpy(&str[i], header, 1);
	}
	else
		return (mb_error2(11));
	return (mb_move_header_end(str, i));
}
