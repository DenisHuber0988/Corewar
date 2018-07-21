/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:03:16 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/19 14:45:35 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/virtual_machine.h"

static void	init_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
		vm->arena[i++] = '0';
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
	ft_bzero(vm->n, sizeof(vm->n));
	ft_bzero(vm->a, sizeof(vm->a));
	init_arena(vm);
}
