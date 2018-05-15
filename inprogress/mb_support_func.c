/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:21:45 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/13 14:21:46 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** t_lab structure initiation.
*/

t_lab	*mb_asmlabel_initiation(t_lab *lab, char *str)
{
	int		length;
	t_lab	*fresh;

	length = 0;
	if (!(fresh = (t_lab*)malloc(sizeof(t_lab))))
		return (NULL);
	while (str[length] != LABEL_CHAR)
		length++;
	fresh->position = 0;
	fresh->name = NULL;
	fresh->next = NULL;
	fresh->position = g_position;
	fresh->name = ft_strsub(str, 0, length);
	fresh->next = lab;
	return (fresh);
}

/*
** Free lable list.
*/

int		mb_asmlabel_free(t_lab *lab)
{
	t_lab	*n;

	n = lab->next;
	while (n)
	{
		lab->next = NULL;
		free(lab->name);
		free(lab);
		lab = n;
		n = lab->next;
	}
	free(lab->name);
	free(lab);
	return (1);
}

/*
** Initiate global variables.
*/

void	mb_globalvar_initiation(void)
{
	g_str = 0;
	g_position = 0;
	g_temporary = 0;
}

/*
** Checking program arguments.
*/

int		mb_check_arguments(int ac)
{
	if (ac == 2)
		ft_printf("You need to put one champ please.\n");
	return (1);
}

/*
** Header initiation.
*/

t_header	*mb_asmheader_initiation(void)
{
	t_header	*fresh;

	if (!(fresh = (t_header*)malloc(sizeof(t_header))))
		return (NULL);
	if (fresh != NULL)
	{
		fresh->prog_size = 0;
		fresh->magic = COREWAR_EXEC_MAGIC;
		ft_bzero(fresh->comment, COMMENT_LENGTH);
		ft_bzero(fresh->prog_name, PROG_NAME_LENGTH);
	}
	return (fresh);
}
