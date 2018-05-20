/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 01:24:20 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 01:24:22 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_err(char	*str, int err)
{
	ft_putendl_fd(str, 2);
	return (err);
}

int		mb_label_err(char *line, int err)
{
	ft_printf("There is no label %s while attempting 
		to dereference symbol %s.\n", line, line);
	return (err);
}

int		mb_lexic_err(t_symbol symbol, int err)
{
	ft_printf("Lexical error in line: %d, column %d.\n", symbol.str, symbol.column);
	return (err);
}
