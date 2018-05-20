/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_lable2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 06:14:12 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 06:14:13 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_label_id(char *lab)
{
	int		id;
	t_list	*labels;

	id = 0;
	labels = mb_get_lable()->labels;
	while (labels)
	{
		if (labels->content)
			if (!ft_strcmp(labels->content, lab))
				return (id);
		id++;
		labels = labels->next;
	}
	return (-1);
}

int		mb_label_val(char *lab, int id)
{
	t_list	*l;

	l = mb_get_lable()->labels;
	while (l)
	{
		if (l->content)
			if (!ft_strcmp(l->content, lab))
				return (l->content_size - id);
		l = l->next;
	}
	return (INT_MAX);
}
