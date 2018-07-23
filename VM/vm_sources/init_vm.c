/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:03:16 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/23 18:32:54 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

void		init_champ(t_vm *vm, t_player *player, int i)
{
	player = &vm->player[i];
	ft_bzero(player->name, PROG_NAME_LENGTH);
	ft_bzero(player->comment, COMMENT_LENGTH);
	ft_bzero(player->code, CHAMP_MAX_SIZE);
	player->number = vm->n[i];
	if (vm->n[i] == -1)
		player->number = i + 1;
	player->address = vm->a[i];
}

void		init(t_vm *vm, int ac, char **av)
{
	vm->av = av;
	vm->ac = ac;
	vm->v = 0;
	vm->cursors = 0;
	vm->dump = -1;
	vm->cycle = 0;
	vm->nbr_players = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->check = 0;
	vm->nbr_live = 0;
	vm->last_live = 0;
	ft_memset(vm->n, -1, sizeof(vm->n));
	ft_memset(vm->a, -1, sizeof(vm->a));
	ft_memset(vm->arena, '0', sizeof(vm->arena));
}
