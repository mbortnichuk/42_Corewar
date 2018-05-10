/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:53:51 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/10 16:53:52 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_parsefile(t_file *f)
{
	t_list	*temp;

	temp = f->strs;
	while (temp)
	{
		if (!mb_iscomment(STR))
		{
			if (STR->type != LABEL)
				STR->type = EXECUTABLE;
			if (!(f->header.prog_name[0]))
				
		}
	}
}
