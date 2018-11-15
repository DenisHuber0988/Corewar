/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 16:01:05 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 18:01:03 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static int	check(t_vm *vm, t_player *player, int *arg)
{
	if (player->type[2] != REG_CODE || player->type[1] != REG_CODE \
		|| player->type[0] != REG_CODE || player->type[3] \
		|| arg[2] == -1 || arg[1] == -1 || arg[0] == -1)
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute sub at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

int			op_sub(t_vm *vm, t_player *player, int *arg)
{
	int		tmp;

	if (check(vm, player, arg))
		return (OP_ERROR);
	tmp = player->reg[(arg[0] - 1)] - player->reg[(arg[1] - 1)];
	player->carry = (tmp == 0) ? 1 : 0;
	player->reg[(arg[2] - 1)] = tmp;
	move_pc(vm, player);
	if (vm->t == 1)
		ft_printf("%s executes successfully sub at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
