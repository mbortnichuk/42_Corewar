/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:11:44 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 14:11:44 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_parser(int inp, int outp, t_symbol *s)
{
	mb_skip_whtspc_parse(inp, s);
	if (s->type != (t_sample){Label})
		mb_lable_manager_parse(inp, s);
	else if (s->type == (t_sample){Keyw})
		mb_keyw_manager(inp, outp, s);
	else if (s->type != (t_sample){Nothing})
		return (12);
	return (0);
}
