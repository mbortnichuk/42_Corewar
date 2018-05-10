/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:15:12 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/10 17:15:13 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	mb_check_asm_arg(/*t_file *f, */int argc, char *argv[])
{
	if (argc == 1)
		mb_asm_err("File does not attached. [Usage: ./asm filename]\n");
	else if (argc == 3)
	{
		if (!(argv[2][0] == '-'))
			mb_asm_err("Cannot recognize option. [Usage: ./asm filename]\n");
		else
			mb_asm_err("Too many files attached. [Usage: ./asm filename]\n");
	}
	else if (argc != 2)
		mb_asm_err("Too many files entered. [UsageL ./asm filename]\n");
	return ;
}
