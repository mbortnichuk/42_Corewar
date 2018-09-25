/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:32:15 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/15 14:32:20 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_vm.h"

static int				get_place(int sorted_nb, unsigned int champ_count)
{
	int			res;
	int			shift;

	res = 0;
	shift = 0;
	if (champ_count == 1 || sorted_nb == 0)
		return (res);
	else
	{
		shift = (MEM_SIZE / champ_count);
		res = shift * sorted_nb;
	}
	return (res);
}

static t_champ			*sort_champ(t_champ *lst, t_champ *head)
{
	t_info		tmp1;
	t_header	tmp2;

	while (lst->next)
	{
		if (lst->fileinfo.id < lst->next->fileinfo.id)
		{
			tmp1 = lst->fileinfo;
			tmp2 = lst->header;
			lst->fileinfo = lst->next->fileinfo;
			lst->header = lst->next->header;
			lst->next->fileinfo = tmp1;
			lst->next->header = tmp2;
			lst = head;
		}
		else
			lst = lst->next;
	}
	lst = head;
	return (lst);
}

void					place_champs(t_core *core)
{
	t_champ		*lst;
	int			pos;

	core->champ = sort_champ(core->champ, core->champ);
	lst = core->champ;
	core->i = 0;
	while (core->i < core->champ_count)
	{
		lst->fileinfo.colour_nbr = (core->i + 1);
		introduce(lst, (core->i + 1));
		(lseek(lst->fileinfo.fd, CODE_POS, SEEK_SET) < 0) ? err(4) : 0;
		pos = get_place(core->i, core->champ_count);
		if ((read(lst->fileinfo.fd, (core->map + pos), CHAMP_MAX_SIZE)) < 0)
			err(4);
		create_proc(&core->proc, lst->fileinfo.id, pos, (core->i + 1));
		lst = lst->next;
		core->i++;
	}
}
