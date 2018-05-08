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

int main(/*int argc, char **argv*/)
{
	t_file	*f;
	if (!(f = (t_file*)malloc(sizeof(t_file))))
		return (EXIT_FAILURE);
	mb_initfile(f);

}
