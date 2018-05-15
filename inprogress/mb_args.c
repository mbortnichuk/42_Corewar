/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:37:39 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/15 10:37:40 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check the validity of the arguments of each operation.
*/

int		mb_check_arguments1(char **str, int op)
{
	if (op == 3 && mb_check_correct_register(str, 1) && (mb_check_indirect(str, 0) || \
		mb_check_correct_register(str, 0)))
		return (1);
	if ((op == 4 || op == 5) && mb_check_correct_register(str, 1) && \
		mb_check_correct_register(str, 1) && mb_check_correct_register(str, 0))
		return (1);
	if ((op == 10 || op == 14) && (mb_directory_check(str, op, 1) || \
		mb_check_correct_register(str, 1) || mb_check_indirect(str, 1)) && \
		(mb_directory_check(str, op, 1) || mb_check_correct_register(str, 1)) && \
		mb_check_correct_register(str, 0))
		return (1);
	return (mb_error1(8));
}

int		mb_check_arguments2(char **str, int op)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
	if ((op == 1 || op == 9 || op == 12 || op == 15) && mb_directory_check(str, op, 0))
		return (1);
	if ((op == 2 || op == 13 ) && (mb_directory_check(str, op, 1) || mb_check_indirect(str, 1)) && \
		mb_check_correct_register(str, 0))
		return (1);
	if ((op == 6 || op == 7 || op == 8) && ((mb_directory_check(str, op, 1) || \
		mb_check_correct_register(str, 1) || mb_check_indirect(str, 1)) && \
		(mb_directory_check(str, op, 1) || mb_check_correct_register(str, 1) || \
			mb_check_indirect(str, 1)) && mb_check_correct_register(str, 0)))
		return (0);
	if (op == 11 && mb_check_correct_register(str, 1) && (mb_directory_check(str, op, 1) || \
		mb_check_correct_register(str, 1) || mb_check_indirect(str, 1)) && \
		(mb_directory_check(str, op, 0) || mb_check_correct_register(str, 0)))
		return (1);
	if (op == 16 && mb_check_correct_register(str, 0))
		return (1);
	return (mb_check_arguments1(str, op));
}
