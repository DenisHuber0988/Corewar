/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:57:41 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 17:59:14 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static int		check(t_vm *vm, t_player *player, int *arg)
{
	if (arg[1] == -1 || player->type[1] != REG_CODE || player->type[0] == -1 \
			|| (player->type[0] != DIR_CODE && player->type[0] != IND_CODE) \
			|| player->type[3])
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute lld at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

static void		recup(t_vm *vm, t_player *player, int index, int adr)
{
	int		tmp;
	int		param[2];

	tmp = 0;
	ft_bzero(param, 2);
	player->arg[index] = 0;
	while (tmp < 2)
	{
		param[tmp] = vm->arena[(adr + tmp) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 2)
	{
		player->arg[index] += param[tmp++];
		if (tmp < 2)
			player->arg[index] <<= 8;
	}
}

int				op_lld(t_vm *vm, t_player *player, int *arg)
{
	int		adr;

	if (check(vm, player, arg) || player->type[3])
		return (OP_ERROR);
	if (player->type[0] == DIR_CODE)
		player->reg[(arg[1] - 1)] = arg[0];
	else
	{
		adr = (player->address + player->pc + (arg[0]));
		recup(vm, player, 0, adr);
		player->reg[(arg[1] - 1)] = arg[0];
	}
	player->carry = (arg[0] == 0) ? 1 : 0;
	move_pc(vm, player);
	if (vm->t == 1)
		ft_printf("%s executes successfully lld at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
