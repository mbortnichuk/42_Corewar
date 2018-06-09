/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_assm_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:57:24 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:57:28 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int		magic(unsigned int s)
{
	unsigned char	*d;

	d = (unsigned char *)&s;
	s = (d[3] | d[2] << 8 | d[1] << 16 | d[0] << 24);
	return (s);
}

unsigned int		magic_2(unsigned int s)
{
	unsigned char	*d;

	d = (unsigned char *)&s;
	s = (d[1] | d[0] << 8);
	return (s);
}

void				get_codage(t_assm *assm)
{
	unsigned int	arg_nbr;
	unsigned int	x;

	arg_nbr = g_tab[assm->inst_n].numb_of_arg - assm->args_count + 1;
	if (arg_nbr == 1)
	{
		x = assm->arg_type << 6;
		assm->codage = x & 192;
	}
	else if (arg_nbr == 2)
	{
		x = assm->arg_type << 4;
		assm->codage = (x & 48) | assm->codage;
	}
	else if (arg_nbr == 3)
	{
		x = assm->arg_type << 2;
		assm->codage = (x & 12) | assm->codage;
	}
	if (lseek(assm->fd_cor, HEADER_SIZE + assm->codage_pos, SEEK_SET) < 0)
		error(assm, 16);
	assm->push == 2 ? write(assm->fd_cor, &assm->codage, 1) : 0;
	if (lseek(assm->fd_cor, HEADER_SIZE + assm->count, SEEK_SET) < 0)
		error(assm, 16);
}

int					get_size(t_assm *assm)
{
	int		size;

	size = 0;
	if (assm->arg_type == REG_CODE)
		size = 1;
	else if (assm->arg_type == DIR_CODE)
	{
		if (g_tab[assm->inst_n].dir_size == 1)
			size = 2;
		else
			size = 4;
	}
	else if (assm->arg_type == IND_CODE)
		size = 2;
	return (size);
}

int					get_label_pos(t_assm *assm, char *line)
{
	t_lab_lst	*lst;
	int			len;
	char		*tmp;

	len = 0;
	while (line[len] && line[len] != SEPARATOR_CHAR)
		len++;
	tmp = ft_strsub(line, 0, len);
	lst = assm->lab_lst;
	while (lst)
	{
		if (!ft_strcmp(lst->data, tmp))
		{
			ft_strdel(&tmp);
			return (lst->index - assm->inst_pos);
		}
		lst = lst->next;
	}
	ft_strdel(&tmp);
	return (0);
}
