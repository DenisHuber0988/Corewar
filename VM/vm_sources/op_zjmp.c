/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:42:53 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 18:01:15 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** JUMP IF ZERO
** Jumps to an address passed as parameter 1, if the carry is 1.
** Zjmp does nothing if the carry is null.
*/

static int		recup_dir2(t_vm *vm, t_player *player, int index)
{
	int		pc;
	int		tmp;
	int		param[2];

	tmp = 0;
	pc = player->address + player->pc;
	ft_bzero(param, sizeof(param));
	player->arg[index] = 0;
	while (tmp < 2)
	{
		param[tmp] = vm->arena[((pc + tmp + 1)) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 2)
	{
		player->arg[index] += param[tmp++];
		if (tmp < 2)
			player->arg[index] <<= 8;
	}
	player->tmpc += 2;
	return (player->arg[index]);
}

int				op_zjmp(t_vm *vm, t_player *player, int *arg)
{
	int		adr;
	int		color;

	color = 0;
	arg[0] = recup_dir2(vm, player, 0);
	adr = player->pc + ((short)arg[0] % IDX_MOD);
	if (player->carry)
	{
		vm->c_arena.lpc[(player->address + player->pc) % MEM_SIZE] -= 1;
		if (vm->c_arena.lpc[(player->address + player->pc) % MEM_SIZE] == 0)
			vm->c_arena.color[(player->address + player->pc) % MEM_SIZE] =
				vm->c_arena.lcolor[(player->address + player->pc) % MEM_SIZE];
		player->pc = adr;
		adr = (player->address + player->pc) % MEM_SIZE;
		vm->c_arena.lpc[adr] += 1;
		if (vm->c_arena.lpc[adr] == 1)
			vm->c_arena.lcolor[adr] = vm->c_arena.color[adr];
		vm->c_arena.pc[adr] = player->color;
		if (vm->t == 1)
			ft_printf("%s executes successfully zjmp at cycle [%d].\n",
			player->name, vm->cycle);
	}
	else
		move_pc(vm, player);
	return (OP_SUCCESS);
}
