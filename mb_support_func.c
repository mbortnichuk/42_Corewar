/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:16:52 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/06 19:16:53 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	mb_col_reset_fd(int f)
{
	ft_putstr_fd(RC, f);
}

static void	mb_col_switch_fd(char *col, int f)
{
	ft_putstr_fd(col, f);
}

static void	mb_putstr_col_fd(char *str, char *col, int f)
{
	mb_col_switch_fd(col, f);
	ft_putstr_fd(str, f);
	mb_col_reset_fd(f);
}

void	mb_putstr_col(char *str, char *col)
{
	mb_putstr_col_fd(str, col, 1);
}

int		mb_haslabel(char *line)
{
	register int i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		++i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != SEPARATOR_CHAR)
		++i;
	--i;
	if (line[i] == LABEL_CHAR)
		return (i);
	return (0);
}
