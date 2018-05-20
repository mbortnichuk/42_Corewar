/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 00:16:08 by mbortnic          #+#    #+#             */
/*   Updated: 2018/05/18 00:16:10 by mbortnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "./libft/libft.h"

# include <fcntl.h>
# include <limits.h>

# include "op.h"

# define OPP(id)	g_tab[id]

# define WHTSPACE	"\n\t\r\v\f "
# define SYMBOL_CHR	"+-,.:#%"
# define COMMENT_CHR2	';'

/*t_op	g_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1},
	{"aff", 1, {T_REG}, 16, 2, 1, 0}
};*/

typedef struct s_lab	t_lab;
typedef struct s_symbol	t_symbol;
// typedef enum e_sample	t_sample;
typedef struct s_chr	t_chr;
typedef struct s_argum	t_argum;
// typedef struct s_op		t_op;

struct s_lab
{
	t_list	*labels;
	int		position;
};

typedef enum e_sample
{
	Unknwn = -1,
	Nothing = 0,
	Whtspc,
	Comm,
	Nl,
	Keyw,
	Label,
	Reg,
	Str,
	Symbol,
	Numb
}			t_sample;

struct s_symbol
{
	char	line[COMMENT_LENGTH + 1];
	int		str;
	int		column;
	t_sample	type;
};

struct s_chr
{
	int		str;
	int		column;
	char	c;
};

struct s_argum
{
	int		size;
	int		val;
	char	type;
};

typedef struct s_op
{
	char				*name;
	short				numb_of_arg;
	t_arg_type			arg[3];
	short				opcode;
	short				cycles;
	short				codage;
	char				dir_size;
}				t_op;

/*
** mb_bin.c
*/

unsigned int	mb_rev_32byte(unsigned int n);
unsigned short	mb_rev_16byte(unsigned int n);
unsigned int	mb_read_fix32(int area);
unsigned int	mb_read_fix16(int area);
ssize_t	mb_fix_write(int area, const void *buff, size_t nbt);


/*
** mb_check.c
*/

char	*mb_checkfile(char *file);
int		mb_start_checklable(void);

/*
** mb_err.c
*/

int		mb_err(char	*str, int err);
int		mb_label_err(char *line, int err);
int		mb_lexic_err(t_symbol symbol, int err);

/*
** mb_header1.c
*/

int		mb_parse_head_arg(int inp, t_symbol *s, int i);
int		mb_parse_head(int inp, int outp, t_symbol *s, int *val);
int		mb_header_skip(int inp, t_symbol *s);

/*
** mb_lable1.c
*/

t_lab	*mb_get_lable_use(void);
t_lab	*mb_get_lable(void);
int		mb_add_label(char *lab, int val);
int		mb_label(int inp, int *val);

/*
** mb_lable2.c
*/

int		mb_label_id(char *lab);
int		mb_label_val(char *lab, int id);

/*
** mb_lexic1.c
*/

t_symbol	mb_symbol_update(t_symbol s, t_sample t, char c);
t_chr		mb_label_manager(t_symbol *s, t_chr c, int file_descr);
int		mb_start_manage_lable(int inp, t_symbol *s, int *val);
t_argum	mb_lookin_arguments(int inp, t_symbol *s, int opcode);

/*
** mb_lexic2.c
*/

int		mb_start_skip_whtspc(int inp, t_symbol *s);
int		mb_lookin_opcode(int inp, int *val, t_symbol *s, int opcode);
t_symbol	mb_lexic(int file_descr);
int		mb_start_opcode_manager(int inp, t_symbol *s, int *val);

/*
** mb_lookin1.c
*/

t_argum	mb_lookin_direct(int inp, t_symbol *s, int c, t_argum ar);
t_argum	mb_lookin_indir(int inp, t_symbol *s, t_argum ar);

/*
** mb_parse1.c
*/

t_argum	mb_arg_indir_parse(int inp, t_symbol *s, t_argum ar);
t_argum	mb_arg_dir_parse(int inp, t_symbol *s, int opcode, t_argum ar);
int		mb_opc_parse(int inp, int outp, t_symbol *s, int opcode);
int		mb_keyw_manager(int inp, int outp, t_symbol *s);
int		mb_creator(char *in, char *out);

/*
** mb_parse2.c
*/

int		mb_file_opc_parse(int inp, int outp, int i[2], t_argum ar[3]);
t_argum	mb_argum_parse(int inp, t_symbol *s, int opcode);
int		mb_skip_whtspc_parse(int inp, t_symbol *s);
int		mb_lable_manager_parse(int inp, t_symbol *s);

/*
** mb_parser.c
*/

int		mb_parser(int inp, int outp, t_symbol *s);

/*
** mb_support_func1.c
*/

void	ft_lstaddback(t_list **alst, t_list *new);
int		mb_str_isdigit(char *line);
void	mb_del_lable(void *cont, size_t sz);
int		mb_del(int res);
t_chr	mb_checker(int file_descr);

/*
** mb_support_func2.c
*/

int		mb_is_reg(char *w);
int		mb_is_key_word(char *w);
int		mb_get_key_word(char *w);
t_chr	mb_line_manager(t_symbol *s, t_chr c, int file_descr);
t_chr	mb_whtsp_manager(t_symbol *s, t_chr c, int file_descr);

extern	t_op	g_tab[17];

#endif
