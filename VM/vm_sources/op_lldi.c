/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:58:53 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 18:00:13 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** LONG INDIRECT LOAD
** Calculates an address by additioning parameters 1 + 2.
** Stores the value found at that address in the register specified by param 1.
** The address is not restricted.
** If the value of parameter 1 is zero, the carry is set to 1.
*/

static int		check(t_vm *vm, t_player *player, int *arg)
{
	if ((arg[0] == -1 && player->type[0] == REG_CODE) || \
		(arg[1] == -1 && player->type[1] == REG_CODE) || arg[2] == -1 \
		|| player->type[0] == -1 || player->type[3] \
		|| (player->type[1] != DIR_CODE && player->type[1] != REG_CODE))
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute lldi at cycle [%d].\n",
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

int				op_lldi(t_vm *vm, t_player *player, int *arg)
{
	int		adr;

	if (check(vm, player, arg))
		return (OP_ERROR);
	adr = 0;
	(player->type[0] == REG_CODE) ? adr += player->reg[arg[0] - 1] : 0;
	(player->type[0] == DIR_CODE) ? adr += arg[0] : 0;
	(player->type[0] == IND_CODE) ? adr += recup_adr(vm, (player->address + \
				player->pc + arg[0]) % MEM_SIZE) : 0;
	(player->type[1] == REG_CODE) ? adr += player->reg[arg[1] - 1] : 0;
	(player->type[1] == DIR_CODE) ? adr += arg[1] : 0;
	adr = (player->address + player->pc + adr) % MEM_SIZE;
	recup(vm, player, 0, adr);
	player->reg[arg[2] - 1] = arg[0];
	move_pc(vm, player);
	player->carry = (player->reg[arg[2] - 1] == 0) ? 1 : 0;
	if (vm->t == 1)
		ft_printf("%s executes successfully lldi at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
