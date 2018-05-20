/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 07:27:46 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 07:27:47 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		mb_file_opc_parse(int inp, int outp, int i[2], t_argum ar[3])
{
	int k;

	k = i[0];
	while (k++ < 4)
		inp = inp << 2;
	k = -1;
	if (g_tab[i[1]].codage)
	{
		mb_fix_write(outp, &inp, 1);
		mb_get_lable()->position++;
	}
	while (++k < i[0])
	{
		mb_fix_write(outp, &(ar[k].val), ar[k].size);
		mb_get_lable()->position += ar[k].size;
	}
	mb_get_lable()->position++;
	return (0);
}

t_argum	mb_argum_parse(int inp, t_symbol *s, int opcode)
{
	t_argum	ar;

	ar = (t_argum){-1, -1, -1};
	while (s->type == (t_sample){Whtspc})
		*s = mb_lexic(inp);
	if (s->type == (t_sample){Symbol})
	{
		if (*(s->line) == DIRECT_CHAR)
			ar = mb_arg_dir_parse(inp, s, opcode, ar);
		else
			ar = mb_arg_indir_parse(inp, s, ar);
	}
	else if (s->type == (t_sample){Numb})
		ar = (t_argum){T_IND, ft_atoi(s->line), IND_SIZE};
	else if (s->type == (t_sample){Reg})
		ar = (t_argum){T_REG, ft_atoi(s->line + 1), 1};
	while ((*s = mb_lexic(inp)).type == (t_sample){Whtspc})
		;
	return (ar);
}

int		mb_skip_wthpsc_parse(int inp, t_symbol *s)
{
	while (s->type == (t_sample){Whtspc} || s->type == (t_sample){Nl})
		*s = mb_lexic(inp);
	return (0);
}

int		mb_lable_manager_parse(int inp, t_symbol *s)
{
	if ((*s = mb_lexic(inp)).type != (t_sample){Symbol} || *(s->line) != LABEL_CHAR)
		return (5);
	*s = mb_lexic(inp);
	return (0);
}
