/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:14:25 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/07 18:14:26 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_file	*f;
	if (!(f = (t_file*)malloc(sizeof(t_file))))
		return (EXIT_FAILURE);
	mb_initfile(f);
	mb_check_asm_arg(/*f, */argc, argv);
	printf("%s\n", argv[0]);
	if (mb_readfile(f) == EXIT_FAILURE)
		//printf("%s\n", f->);
		mb_asm_err("File reading has failed.\n");
	return (EXIT_SUCCESS);
}
