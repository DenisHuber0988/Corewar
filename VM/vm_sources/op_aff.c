/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:51:39 by aschukin          #+#    #+#             */
/*   Updated: 2018/10/05 15:28:38 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** Cette instruction est suivie d’un octet de paramétrage pour
** décrire les paramètres. Elle prend en paramètre un registre
** et affiche le caractère dont le code ascii est présent dans ce registre
** (base 10).
** (un modulo 256 est appliqué au code ascii, le caractère est affiché
** sur la sortie standard)
** Ex : ld %42,r3
**     aff r3     ==> affiche ’*’ sur la sortie standard
*/

static int	check(t_vm *vm, t_player *player, int *arg)
{
	if (player->type[0] != REG_CODE || arg[0] == -1 || player->type[3])
	{
		if (vm->t == 1)
			ft_printf("%s failed to execute aff at cycle [%d].\n",
			player->name, vm->cycle);
		move_pc(vm, player);
		return (1);
	}
	return (0);
}

int			op_aff(t_vm *vm, t_player *player, int *arg)
{
	if (check(vm, player, arg))
		return (OP_ERROR);
	if (player->index_aff > AFF_MAX || !(player->reg[arg[0] - 1] % 256))
	{
		ft_memmove(&(vm->taunt), &(player->taunt), AFF_MAX);
		ft_memmove(&(vm->taunt_name), &(player->name), PROG_NAME_LENGTH);
		vm->taunt_cycle = vm->cycle;
		vm->taunt_nb = player->number;
		if (vm->t > 0)
		{
			ft_printf("Player [%s] n°[%d] says at cycle [%d]: '%s' !\n",
				player->name, player->number, vm->cycle, player->taunt);
			(vm->v >= 0) ? usleep(500000) : 0;
		}
		ft_memset(player->taunt, 0, AFF_MAX + 1);
		player->index_aff = 0;
	}
	else
		player->taunt[player->index_aff++] = (player->reg[arg[0] - 1] % 256);
	move_pc(vm, player);
	return (OP_SUCCESS);
}
