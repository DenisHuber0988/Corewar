/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:55:17 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 22:55:37 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static int	check(t_vm *vm, t_player *player, int *arg)
{
	if (player->type[0] != REG_CODE || arg[0] == -1 || player->type[3] \
		|| (player->type[1] != REG_CODE && player->type[1] != IND_CODE))
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute st at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

int			op_st(t_vm *vm, t_player *player, int *arg)
{
	int		adr;
	int		i;

	i = 0;
	if (check(vm, player, arg))
		return (OP_ERROR);
	if (player->type[1] == REG_CODE)
		player->reg[arg[1] - 1] = player->reg[arg[0] - 1];
	else
	{
		adr = (player->address + player->pc + ((short)arg[1] % IDX_MOD));
		adr = (adr < 0) ? MEM_SIZE + adr : (adr % MEM_SIZE);
		ft_vm_move(vm->arena, &player->reg[arg[0] - 1], \
				REG_SIZE, (adr % MEM_SIZE) + REG_SIZE);
		ft_color_move(vm, player->color, adr, REG_SIZE);
	}
	move_pc(vm, player);
	if (vm->t == 1)
		ft_printf("%s executes successfully st at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
