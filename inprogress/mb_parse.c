/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:02:48 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 14:02:49 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_parse(char *champ, t_header *header/*, int ch*/)
{
	t_lab	*lab;
	char	*file;
	int		position;
	int		file_descr;

	file = NULL;
	position = 0;
	lab = 0;
	mb_check_champion(champ);
	if ((file_descr = open(champ, O_RDONLY, 0555)) == -1)
		return (ERROR);
	mb_handle_name_comm(file_descr, header);
	lab = mb_parseline(file_descr, &file);
	mb_check_duplicate_label(lab);
	if (mb_label_exists(lab, file) == 0)
		return (mb_error2(12));
	// mb_reader(lab, header, champ, file);
	if (file && file[0])
		free(file);
	if (lab)
		mb_asmlabel_free(lab);
	return (0);
}