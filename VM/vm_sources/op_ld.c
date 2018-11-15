/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:36:56 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 18:00:27 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static int		check(t_vm *vm, t_player *player, int *arg)
{
	if (player->type[1] != REG_CODE || arg[1] == -1 ||
	(player->type[0] != DIR_CODE && player->type[0] != IND_CODE) ||
		player->type[3])
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute ld at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

static void		recup(t_vm *vm, t_player *player, int index, int adr)
{
	int		tmp;
	int		param[4];

	tmp = 0;
	ft_bzero(param, 4);
	player->arg[index] = 0;
	while (tmp < 4)
	{
		param[tmp] = vm->arena[(adr + tmp) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 4)
	{
		player->arg[index] += param[tmp++];
		if (tmp < 4)
			player->arg[index] <<= 8;
	}
}

int				op_ld(t_vm *vm, t_player *player, int *arg)
{
	int		adr;

	if (check(vm, player, arg))
		return (OP_ERROR);
	if (player->type[0] == DIR_CODE)
		player->reg[(arg[1] - 1)] = arg[0];
	else
	{
		adr = (player->address + player->pc + ((short)arg[0] % IDX_MOD));
		recup(vm, player, 0, adr);
		player->reg[(arg[1] - 1)] = player->arg[0];
	}
	move_pc(vm, player);
	player->carry = (!arg[0]) ? 1 : 0;
	if (vm->t == 1)
		ft_printf("%s executes successfully ld at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
