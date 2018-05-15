/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:37:04 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/14 14:37:05 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Put the valid line in the array.
*/

char	*mb_putline_infile(char *str, int i, char *f)
{
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] && str[i] != COMMENT_CHAR && str[i] != ';' && \
		mb_checkline(&str[i]))
		f = mb_freejoin(&str[i], f);
	free(str);
	str = NULL;
	return (f);
}

/*
** Retrieve the name of the label, position int a chained list.
*/

t_lab	*mb_parseline(int file_descr, char **file)
{
	int i;
	char *str;
	t_lab	*lab;

	str = NULL;
	lab = NULL;
	while (!(i = 0) && get_next_line(file_descr, &str) > 0)
	{
		g_str++;
		while (str[i] == '\t' || str[i] == ' ')
			i++;
		if (str[i] && str[i] != COMMENT_CHAR && str[i] != ';' && \
			mb_checklabel(str) >= 1)
		{
			lab = mb_asmlabel_initiation(lab, str);
			while (str[i] != LABEL_CHAR)
				i++;
			i++;
		}
		*file = mb_putline_infile(str, i, *file);
	}
	free(str);
	return (lab);
}
