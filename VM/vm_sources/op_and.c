/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:51:58 by aschukin          #+#    #+#             */
/*   Updated: 2018/09/25 18:00:02 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static int		check(t_vm *vm, t_player *player, int *arg)
{
	int		i;

	i = 0;
	if ((player->type[0] == REG_CODE && arg[0] == -1) || player->type[0] == -1
			|| (player->type[1] == REG_CODE && arg[1] == -1) || player->type[3]
			|| (player->type[1] == -1 || (player->type[2] == -1)))
		i++;
	if (arg[2] == -1
	|| player->type[2] != REG_CODE
	|| i)
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute and at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

static int		recup_index(t_vm *vm, t_player *player, int index, short adr)
{
	int		pc;
	int		tmp;
	int		param[4];

	tmp = 0;
	pc = player->address + player->pc;
	ft_bzero(param, 4);
	player->arg[index] = 0;
	while (tmp < 4)
	{
		param[tmp] = vm->arena[((pc + tmp) + (adr % IDX_MOD)) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 4)
	{
		player->arg[index] += param[tmp++];
		if (tmp < 4)
			player->arg[index] <<= 8;
	}
	return (player->arg[index]);
}

int				op_and(t_vm *vm, t_player *player, int *arg)
{
	if (check(vm, player, arg))
		return (OP_ERROR);
	if (player->type[0] == REG_CODE)
		arg[0] = player->reg[arg[0] - 1];
	else if (player->type[0] == IND_CODE)
		arg[0] = recup_index(vm, player, 0, arg[0]);
	if (player->type[1] == REG_CODE)
		arg[1] = player->reg[arg[1] - 1];
	else if (player->type[1] == IND_CODE)
		arg[1] = recup_index(vm, player, 1, arg[1]);
	player->reg[arg[2] - 1] = arg[0] & arg[1];
	player->carry = (player->reg[arg[2] - 1] == 0) ? 1 : 0;
	move_pc(vm, player);
	if (vm->t == 1)
		ft_printf("%s executes successfully and at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
