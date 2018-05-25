/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:02:48 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/25 04:26:37 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strclen(char c, char *line)
{
	int	j;

	j = 0;
	while (line[j] != '\0' && line[j] != c)
		j++;
	return (j);
}

void	mb_init_glob(void)
{
	g_str = 0;
	g_indx = 0;
	g_temporary = 0;
}

int			mb_move_i(char *inp_file, int i)
{
	while (inp_file[i] != ',')
		i++;
	i++;
	while (inp_file[i] == '\t' || inp_file[i] == ' ')
		i++;
	return (i);
}

t_header	*mb_init_header(void)
{
	t_header	*fresh;

	if (!(fresh = (t_header*)malloc(sizeof(t_header))))
		return (NULL);
	if (fresh != NULL)
	{
		fresh->magic = COREWAR_EXEC_MAGIC;
		fresh->prog_size = 0;
		ft_bzero(fresh->prog_name, PROG_NAME_LENGTH);
		ft_bzero(fresh->comment, COMMENT_LENGTH);
	}
	return (fresh);
}

t_lab		*mb_init_lab(char *str, t_lab *lab)
{
	int			length;
	t_lab		*fresh;

	length = 0;
	if (!(fresh = malloc(sizeof(t_lab))))
		return (NULL);
	while (str[length] != LABEL_CHAR)
		length++;
	fresh->name = NULL;
	fresh->next = NULL;
	fresh->index = 0;
	fresh->name = ft_strsub(str, 0, length);
	fresh->index = g_indx;
	fresh->next = lab;
	return (fresh);
}
