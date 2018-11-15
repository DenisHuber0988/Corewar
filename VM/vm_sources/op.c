/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/09/26 12:28:14 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Move_pc enables to move the pc according to our temporary_pc (tmpc), which
**	goesthrough the different parameters before moving our the process pc
** to the next op.
**	Also, it sets up the color in the color_arena.
**	--> The 'color' integer keeps in memory the color of the present pc, that is
**		the color of the actual player's cursor.
**	--> Then, player->p_color (for previous_color) will keep in memory the color
**		of the case in the VM where the pc will point on the next turn.
**	--> Finally, we give to the new pc in color_arena the value of color.
**
**	To sum it up, at the beginning of each turn, before moving the pc, we give
**	the present case its previous color.
*/

void	move_pc(t_vm *vm, t_player *player)
{
	if (!player)
		return ;
	vm->c_arena.lpc[(player->address + player->pc) % MEM_SIZE] -= 1;
	if (vm->c_arena.lpc[(player->address + player->pc) % MEM_SIZE] == 0)
		vm->c_arena.color[(player->address + player->pc) % MEM_SIZE] = \
			vm->c_arena.lcolor[(player->address + player->pc) % MEM_SIZE];
	player->pc = (player->tmpc + 1) % 0xffff;
	vm->c_arena.lpc[(player->address + player->pc) % MEM_SIZE] += 1;
	if (vm->c_arena.lpc[(player->address + player->pc) % MEM_SIZE] == 1)
		vm->c_arena.lcolor[(player->address + player->pc) % MEM_SIZE] = \
			vm->c_arena.color[(player->address + player->pc) % MEM_SIZE];
	vm->c_arena.pc[(player->address + player->pc) % MEM_SIZE] = player->color;
}

/*
**	Each element in struct t_base (found in virtual_machine.h)
**	corresponds to an element in g_op_tab[], in order of appearance.
**
**	typedef struct		s_base
**	{
**		char			*name;
**		int				nb_arg;
**		int				type[4];
**		int				opc;
**		int				cycle;
**		char			*comment;
**		int				carry;
**		int				direct_bit;
**		int				(*ft_op)(t_vm*, t_player*, int*);
**	}					t_base;
*/

t_base	g_op_tab[] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &op_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &op_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &op_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &op_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, \
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &op_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, \
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &op_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, \
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &op_xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &op_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, \
		"load index", 1, 1, &op_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, \
		"store index", 1, 1, &op_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &op_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, \
		"long load index", 1, 1, &op_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &op_lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &op_aff},
};
