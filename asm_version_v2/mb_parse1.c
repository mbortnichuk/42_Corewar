/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mb_parse1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 05:44:31 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 05:44:32 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_argum	mb_arg_indir_parse(int inp, t_symbol *s, t_argum ar)
{
	int		state;

	if (*(s->line) == '+' || *(s->line) == '-')
	{
		state = (*(s->line) == '+') ? 1 : -1;
		*s = mb_lexic(inp);
		if (s->type == (t_sample){Numb})
			ar = (t_argum){T_IND, state * ft_atoi(s->line), IND_SIZE};
	}
	else if (*(s->line) == LABEL_CHAR)
	{
		*s = mb_lexic(inp);
		if (mb_label_id(s->line) != -1)
			ar = (t_argum){T_IND, mb_label_val(s->line, \
				mb_get_lable()->position), IND_SIZE};
	}
	return (ar);
}

t_argum	mb_arg_dir_parse(int inp, t_symbol *s, int opcode, t_argum ar)
{
	int state;

	*s = mb_lexic(inp);
	if (s->type == (t_sample){Symbol})
	{
		if (*(s->line) == '+' || *(s->line) == '-')
		{
			state = (*(s->line) == '+') ? 1 : -1;
			*s = mb_lexic(inp);
			if (s->type == (t_sample){Numb})
				ar = (t_argum){T_DIR, state * ft_atoi(s->line), (g_tab[opcode].dir_size) ? DIR_SIZE / 2 : DIR_SIZE};
		}
		else if (*(s->line) == LABEL_CHAR)
		{
			*s = mb_lexic(inp);
			if (mb_label_id(s->line) != -1)
				ar = (t_argum){T_DIR, mb_label_val(s->line, mb_get_lable()->position), g_tab[opcode].dir_size ? DIR_SIZE / 2 : DIR_SIZE};
		}
	}
	else if (s->type == (t_sample){Numb})
		ar = (t_argum){T_DIR, ft_atoi(s->line), (g_tab[opcode].dir_size) ? DIR_SIZE / 2 : DIR_SIZE};
	return (ar);
}

int		mb_opc_parse(int inp, int outp, t_symbol *s, int opcode)
{
	int		i[2];
	t_argum	ar[3];
	int		param;

	param = 0;
	i[0] = -1;
	i[1] = opcode;
	*s = mb_lexic(inp);
	mb_fix_write(outp, &(g_tab[opcode].opcode), 1);
	while (++i[0] < g_tab[opcode].numb_of_arg)
	{
		if (i[0] && s->type == (t_sample){Symbol} && *(s->line) == SEPARATOR_CHAR)
			*s = mb_lexic(inp);
		else if (i[0])
			return (2);
		if ((ar[i[0]] = mb_argum_parse(inp, s, opcode)).size == -1)
			return (1);
		if (!(g_tab[opcode].arg[i[0]] & ar[i[0]].type))
			return (3);
		ar[i[0]].type = (ar[i[0]].type == T_IND) ? IND_CODE : ar[i[0]].type;
		param = (param << 2) + ar[i[0]].type;
	}
	mb_file_opc_parse(param, outp, i, ar);
	return (0);
}

int		mb_keyw_manager(int inp, int outp, t_symbol *s)
{
	if (mb_opc_parse(inp, outp, s, mb_get_key_word(s->line)))
		return (6);
	while (s->type != (t_sample){Nl})
	{
		if (s->type != (t_sample){Whtspc})
			return (7);
		*s = mb_lexic(inp);
	}
	return (0);
}

int		mb_creator(char *in, char *out)
{
	int		val;
	int		input;
	int		output;
	t_symbol	s;

	if ((input = open(in, O_RDONLY)) < 0)
		return (mb_err("Sorry, cannot read passed file as program argument.", 1));
	if (mb_label(input, &val))
		return (-1);
	if ((output = open(out, O_CREAT | O_RDWR, 0644)) < 0)
		return (3);
	if (mb_parse_head(input, output, &s, &val))
		return (4);
	while (s.type != (t_sample){Nothing})
		if (mb_parser(input, output, &s))
			return (1);
	return (0);
}
