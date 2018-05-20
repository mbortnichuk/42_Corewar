/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_support_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 01:29:21 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 01:29:22 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int		mb_str_isdigit(char *line) // check if it's working correctly later.
{
	int i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	mb_del_lable(void *cont, size_t sz)
{
	ft_strdel((char **)&cont);
	sz = 0;
}

int		mb_del(int res)
{
	ft_lstdel(&(mb_get_lable()->labels), &mb_del_lable);
	ft_lstdel(&(mb_get_lable_use()->labels), &mb_del_lable);
	return (res);
}

t_chr	mb_checker(int file_descr)
{
	char	chr;
	static int	column = 0;
	static int	str = 1;

	column++;
	if (read(file_descr, &chr, 1) > 0)
	{
		if (chr == '\n')
		{
			column = 0;
			str++;
		}
		return ((t_chr){chr, column, str});
	}
	else
		return ((t_chr){-1, column, str});
}
