/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:30:40 by iosypenk          #+#    #+#             */
/*   Updated: 2018/05/31 18:30:42 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_VM_H

# define STRUCTS_VM_H

# include "../corewar.h"

typedef struct			s_info
{
	int					id;
	int					fd;
	int					colour_nbr;
	char				*filename;
}						t_info;

typedef struct			s_champ
{
	int					last_live;
	int					lives_in_per;
	t_header			header;
	t_info				fileinfo;
	struct s_champ		*next;
}						t_champ;

typedef struct			s_proc
{
	int					id;
	int					carry;
	bool				live;
	int					cd;
	unsigned int		prev_pc;
	unsigned int		pc;
	int					colour_nbr;
	struct s_proc		*next;
	unsigned int		reg[REG_NUMBER + 1];
}						t_proc;

typedef struct			s_make_dim
{
	int					cd;
	unsigned int		adr;
	int					color;
	struct s_make_dim	*next;
}						t_make_dim;

typedef struct			s_vis
{
	int					key;
	int					width;
	int					height;
	int					speed;
	int					pause;
	int					*field_carry;
	int					y_b_menu;
	int					x;
	int					y;
	int					bold;
	unsigned int		ret;
	WINDOW				*big;
	MEVENT				mouse;
	t_proc				*proc;
	t_make_dim			*dim;
}						t_vis;

typedef struct			s_core
{
	t_vis				vis;
	t_champ				*champ;
	t_proc				*proc;
	int					cycles_to_die;
	unsigned char		map[MEM_SIZE];
	unsigned int		i;
	unsigned int		champ_count;
	int					tmp;
	int					last;
	int					dump_stop;
	int					vis_flag;
	int					a_flag;
}						t_core;

typedef struct			s_op
{
	char				*name;
	short				numb_of_arg;
	unsigned char		arg[3];
	short				opcode;
	short				cycles;
	short				codage;
	char				dir_size;
}						t_op;

#endif
