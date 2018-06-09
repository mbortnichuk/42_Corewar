/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_push_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:58:09 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:58:10 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			parse_arg(char *line)
{
	int		i;

	if (line[0] == DIRECT_CHAR)
		return (DIR_CODE);
	else if (line[0] == 'r')
	{
		i = 0;
		while (line[i])
		{
			if (line[0] == 'r' && ft_isdigit(line[i]) &&
				(line[i + 1] == '\0' || line[i + 1] == SEPARATOR_CHAR))
			{
				return (REG_CODE);
			}
			i++;
		}
	}
	else
	{
		return (IND_CODE);
	}
	return (0);
}

static void			ind_args(t_assm *assm, char *line)
{
	int			nbr;

	if (!ft_strncmp(line, ":", 1))
		nbr = get_label_pos(assm, line + 1);
	else
		nbr = ft_atoi(line);
	assm->magic = magic_2(nbr);
	assm->push == 2 ? write(assm->fd_cor, &assm->magic, 2) : 0;
	assm->count += 2;
}

static void			dir_args(t_assm *assm, char *line)
{
	int		nbr;

	assm->count += get_size(assm);
	if (!ft_strncmp(line, "%:", 2))
		nbr = get_label_pos(assm, line + 2);
	else
		nbr = ft_atoi(line + 1);
	if (get_size(assm) == 2)
	{
		assm->magic = magic_2(nbr);
		assm->push == 2 ? write(assm->fd_cor, &assm->magic, 2) : 0;
	}
	else if (get_size(assm) == 4)
	{
		assm->magic = magic(nbr);
		assm->push == 2 ? write(assm->fd_cor, &assm->magic, 4) : 0;
	}
}

void				push_args(t_assm *assm, char *line)
{
	int		nbr;

	if (assm->args_count == 0)
		assm->args_count = g_tab[assm->inst_n].numb_of_arg;
	assm->arg_type = parse_arg(line);
	(g_tab[assm->inst_n].codage == 1) ? get_codage(assm) : 0;
	if (assm->arg_type == REG_CODE)
	{
		nbr = ft_atoi(line + 1);
		assm->push == 2 ? write(assm->fd_cor, &nbr, 1) : 0;
		assm->count++;
	}
	else if (assm->arg_type == DIR_CODE)
		dir_args(assm, line);
	else if (assm->arg_type == IND_CODE)
		ind_args(assm, line);
	assm->args_count--;
}
