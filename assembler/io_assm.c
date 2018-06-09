/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_assm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:57:12 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:57:15 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			assm_init(t_assm *assm)
{
	t_lab_lst	*lst;

	lst = assm->lab_lst;
	while (lst)
	{
		lst->index = 0;
		lst = lst->next;
	}
	assm->line_lst = NULL;
	assm->inst_n = 0;
	assm->args_count = 0;
	assm->arg_type = 0;
	assm->codage = 0;
	assm->codage_pos = 0;
	assm->inst_pos = 0;
	assm->magic = 0;
	assm->push = 0;
}

static void			set_label_index(t_assm *assm, char *line)
{
	t_lab_lst	*lab;
	char		*tmp;
	int			size;

	lab = assm->lab_lst;
	size = (ft_strlen(line) - ft_strlen(ft_strrchr(line, ':')));
	tmp = ft_strsub(line, 0, size);
	while (lab)
	{
		if (!ft_strcmp(lab->data, tmp))
		{
			lab->index = assm->count;
		}
		lab = lab->next;
	}
	ft_strdel(&tmp);
}

static void			push_instr(t_assm *assm, char *line)
{
	assm->inst_n = is_instr_nbr(line);
	assm->inst_pos = assm->count;
	assm->push == 2 ? write(assm->fd_cor, &assm->inst_n, 1) : 0;
	assm->args_count = 0;
	assm->count++;
	(g_tab[assm->inst_n].codage == 1) ? assm->codage_pos = assm->count++ : 0;
}

static void			count_bytes(t_assm *assm)
{
	t_lab_lst	*lst;

	lst = assm->line_lst;
	while (lst)
	{
		if (is_label(lst->data))
			set_label_index(assm, lst->data);
		else if (is_instr_nbr(lst->data) > 0)
			push_instr(assm, lst->data);
		else
			push_args(assm, lst->data);
		lst = lst->next;
	}
	(lseek(assm->fd_cor, CODE_SIZE_POS, SEEK_SET) < 0) ? error(assm, 16) : 0;
	assm->header.prog_size = magic(assm->count);
	assm->push == 2 ? write(assm->fd_cor, &assm->header.prog_size, 4) : 0;
}

void				assembler(t_assm *assm)
{
	assm_init(assm);
	fill_champ_header(assm);
	parse_champ_code(assm);
	while (assm->push < 2)
	{
		assm->push++;
		assm->count = 0;
		lseek(assm->fd_cor, HEADER_SIZE, SEEK_SET) < 0 ? error(assm, 16) : 0;
		count_bytes(assm);
	}
}
