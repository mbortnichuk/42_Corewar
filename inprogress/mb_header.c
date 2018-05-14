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
