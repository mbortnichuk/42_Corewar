/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_vm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:40:25 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/31 18:40:26 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTR_VM_H

# define INSTR_VM_H

# include "../corewar.h"

typedef struct s_core	t_core;
typedef struct s_proc	t_proc;
typedef struct s_champ	t_champ;

/*
**	Instructions
*/

void					game_start(t_core *core);
void					live_inst(t_core *core, t_proc *proc, int inst);
void					ld_inst(t_core *core, t_proc *proc, int inst);
void					st_inst(t_core *core, t_proc *proc, int inst);
void					add_inst(t_core *core, t_proc *proc, int inst);
void					sub_inst(t_core *core, t_proc *proc, int inst);
void					and_inst(t_core *core, t_proc *proc, int inst);
void					or_inst(t_core *core, t_proc *proc, int inst);
void					xor_inst(t_core *core, t_proc *proc, int inst);
void					zjmp_inst(t_core *core, t_proc *proc, int inst);
void					ldi_inst(t_core *core, t_proc *proc, int inst);
void					sti_inst(t_core *core, t_proc *proc, int inst);
void					fork_inst(t_core *core, t_proc *proc, int inst);
void					lld_inst(t_core *core, t_proc *proc, int inst);
void					lldi_inst(t_core *core, t_proc *proc, int inst);
void					lfork_inst(t_core *core, t_proc *proc, int inst);
void					aff_inst(t_core *core, t_proc *proc, int inst);

/*
**	Sup functions
*/

int						four_byte(unsigned char *map, unsigned int adr);
short int				two_byte(unsigned char *map, unsigned int adr);
unsigned int			read_direct(t_core *core, int pos, char label_size);
void					write_to_reg(int value, unsigned int reg_num,
															t_proc *proc);
void					write_to_map(unsigned char map[MEM_SIZE],
											unsigned int value, int adr);
unsigned int			inst_size(int inst, unsigned char codage);
unsigned int			arg_size(int inst, unsigned char codage, int arg_nb);
unsigned char			what_arg(unsigned char codage, int arg_nb);
unsigned int			read_arg(unsigned char *map, unsigned int pc,
													int inst, int arg_nb);
int						if_inst_valid(t_core *core, t_proc *proc, int inst);
unsigned int			arg_type(unsigned char codage, int arg_nb);
int						add_cd_check_valid(t_core *core, t_proc *proc,
																int inst);
int						live_in_period(t_champ *champ);
void					kill_them(t_proc **proc, t_core *core);
void					reset_lives(t_champ *champ, t_proc *proc);
unsigned int			pc_pos(unsigned int dist);
char					*get_winner(t_core *core);
unsigned int			read_arg_no_idx(unsigned char *map,
								unsigned int pc, int inst, int arg_nb);
unsigned int			fit_reg(unsigned int nb);

/*
**	support_tools.c:
*/

typedef struct			s_func
{
	void				(*func)(t_core *core, t_proc *proc, int inst);
}						t_func;

extern t_op				g_tab[17];
unsigned int			g_total_cycles;

static const t_func g_func[] =
{
	{0},
	{&live_inst},
	{&ld_inst},
	{&st_inst},
	{&add_inst},
	{&sub_inst},
	{&and_inst},
	{&or_inst},
	{&xor_inst},
	{&zjmp_inst},
	{&ldi_inst},
	{&sti_inst},
	{&fork_inst},
	{&lld_inst},
	{&lldi_inst},
	{&lfork_inst},
	{&aff_inst}
};

#endif
