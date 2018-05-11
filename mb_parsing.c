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
				mb_check_valid_name(f, STR);
			if (!(f->header.comment[0]))
				mb_check_valid_comment(f, STR);
			if ((STR->type == EXECUTABLE) && /*((mb_tokenize_str(STR) == EXIT_FAILURE)*/ || (!mb_has_valid_parameter(STR)))
				RET_ERR("File parsing has failed.\n", EXIT_FAILURE);
			if (STR->type == LABEL)
				(STR->line)[mb_str_position(STR->line, LABEL_CHAR)] = 0;
			else
				mb_get_linecode_length(STR);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
