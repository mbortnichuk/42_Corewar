/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkravets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:22:10 by vkravets          #+#    #+#             */
/*   Updated: 2018/05/07 19:22:12 by vkravets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include "../corewar.h"

# define COORD_X(x) ((x % 64) * 3) + 1
# define COORD_Y(y) (y / 64)

typedef struct s_core	t_core;
typedef struct s_proc	t_proc;
typedef struct s_champ	t_champ;

void					replace_field(int position, int color, t_core *core);
void					print_first_carry(int index, t_core *core);
void					print_carry(t_core *core);
void					re_print_data(t_core *core);
void					function_for_vis(t_core *core);
void					function_paint_content(t_core *core);
void					set_color(void);
void					function_print_map(t_core *core);
void					color_player(t_proc *proc, unsigned int *i,
															t_core *core);
void					print_top_menu();
void					print_middle_menu(t_core *core);
void					print_bottom_menu(t_core *core);
void					one_player(t_core *core);
void					two_player(t_core *core);
void					three_player(t_core *core);
void					four_player(t_core *core);
int						check_pause(t_core *core);
void					stop_cycles(t_core *core);
void					clean_carry(t_core *core);
void					print_fork_proc(t_core *core);
void					function_print_small(void);
void					re_print_registr(t_core *core);
void					return_color_carry(t_proc *proc, t_core *core);
int						count_procs(t_proc *proc);
void					end_vis(t_core *core);
void					replace_field_dim(t_core *core);
void					kill_old_dim(t_make_dim **head);
void					add_dim(t_make_dim **alst, t_make_dim *new);
t_make_dim				*new_dim(unsigned int adr, int color);

#endif
