/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_instruction_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:21:45 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:15 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check if the instruction name is correct and return 
** the corresponding int.
*/

int			mb_instruction_name2(char *str)
{
	if (ft_strncmp("ldi", str, 3) == 0)
		return (10);
	if (ft_strncmp("ld", str, 2) == 0)
		return (2);
	if (ft_strncmp("fork", str, 4) == 0)
		return (12);
	if (ft_strncmp("st", str, 2) == 0)
		return (3);
	if (ft_strncmp("lldi", str, 4) == 0)
		return (14);
	if (ft_strncmp("lld", str, 3) == 0)
		return (13);
	if (ft_strncmp("lfork", str, 5) == 0)
		return (15);
	if (ft_strncmp("aff", str, 3) == 0)
		return (16);
	return (0);
}

int			mb_instruction_name(char *str)
{
	if (ft_strncmp("live", str, 4) == 0)
		return (1);
	if (ft_strncmp("add", str, 3) == 0)
		return (4);
	if (ft_strncmp("sub", str, 3) == 0)
		return (5);
	if (ft_strncmp("and", str, 3) == 0)
		return (6);
	if (ft_strncmp("or", str, 2) == 0)
		return (7);
	if (ft_strncmp("xor", str, 3) == 0)
		return (8);
	if (ft_strncmp("zjmp", str, 4) == 0)
		return (9);
	if (ft_strncmp("sti", str, 3) == 0)
		return (11);
	return (mb_instruction_name2(str));
}
