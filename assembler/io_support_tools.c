/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_identification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 12:57:48 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/28 12:57:50 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int				check_lab_char(char c)
{
	int			i;

	i = 0;
	if (!c)
		return (0);
	while (LABEL_CHARS[i])
	{
		if (c == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}

int						is_label(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (check_lab_char(line[i - 1]) && line[i] == LABEL_CHAR)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

int						is_instr_nbr(char *line)
{
	int		i;

	i = 1;
	while (i < 17)
	{
		if (!ft_strcmp(line, g_tab[i].name))
		{
			return (i);
		}
		i++;
	}
	return (0);
}

static t_lab_lst		*io_get_lab_lst(t_lab_lst *head)
{
	t_lab_lst		*lst;

	lst = NULL;
	if (head)
	{
		lst = head;
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void					io_create_lab_lst(t_lab_lst **head, char *lab)
{
	t_lab_lst		*new;
	t_lab_lst		*last;

	if (!(new = malloc(sizeof(t_lab_lst))))
		err(0);
	new->data = lab;
	new->index = 0;
	new->next = NULL;
	if ((last = io_get_lab_lst(*head)))
		last->next = new;
	else
		*head = new;
}
