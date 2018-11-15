/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:48:18 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 22:57:43 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** INDIRECT STORE
** Caculates an address by additioning parameters 2 + 3.
** Stores the value of parameter 1 at that address.
** The address is restricted by IDX_MOD.
** If the value of parameter 1 is zero, the carry is set to 1.
*/

static int		check(t_vm *vm, t_player *player, int *arg)
{
	if ((arg[0] == -1 || player->type[0] != REG_CODE) \
		|| (player->type[1] == -1) || (player->type[1] == REG_CODE \
		&& arg[1] == -1) || (arg[2] == -1 && player->type[2] == 1) \
		|| (player->type[2] != DIR_CODE && player->type[2] != REG_CODE) \
		|| player->type[3])
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute sti at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

static int		recup_adr(t_vm *vm, int adr)
{
	int		tmp;
	int		final_adr;
	int		param[2];

	tmp = 0;
	final_adr = 0;
	ft_bzero(param, 2);
	while (tmp < 2)
	{
		param[tmp] = vm->arena[(adr + tmp) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 2)
	{
		final_adr += param[tmp++];
		if (tmp < 2)
			final_adr <<= 8;
	}
	return (final_adr);
}

int				op_sti(t_vm *vm, t_player *player, int *arg)
{
	int		adr;

	adr = 0;
	if (check(vm, player, arg))
		return (OP_ERROR);
	(player->type[1] == REG_CODE) ? adr += player->reg[arg[1] - 1] : 0;
	(player->type[1] == DIR_CODE) ? adr += arg[1] : 0;
	(player->type[1] == IND_CODE) ? adr += recup_adr(vm, (player->address + \
		player->pc + (arg[1] % IDX_MOD)) % MEM_SIZE) : 0;
	(player->type[2] == REG_CODE) ? adr += player->reg[arg[2] - 1] : 0;
	(player->type[2] == DIR_CODE) ? adr += arg[2] : 0;
	adr = (player->address + player->pc + ((short)adr % IDX_MOD)) % MEM_SIZE;
	adr = (adr < 0) ? MEM_SIZE + adr : (adr % MEM_SIZE);
	ft_vm_move(vm->arena, &player->reg[arg[0] - 1], \
			REG_SIZE, (adr % MEM_SIZE) + REG_SIZE);
	ft_color_move(vm, player->color, (adr % MEM_SIZE), REG_SIZE);
	move_pc(vm, player);
	if (vm->t == 1)
		ft_printf("%s executes successfully sti at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
