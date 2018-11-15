/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:33:02 by malek             #+#    #+#             */
/*   Updated: 2018/09/26 12:27:20 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** Loads each player in the arena, one by one.
*/

static void			load(t_vm *vm, t_player *player, int adr)
{
	int i;

	i = 0;
	while (i < player->program_size)
	{
		if (adr + i >= MEM_SIZE)
		{
			ft_memmove(&vm->arena[(adr + i) - MEM_SIZE], &player->code[i], 1);
			ft_memmove(&vm->c_arena.color[(adr + i) - MEM_SIZE],
					&player->color, 1);
		}
		else
		{
			ft_memmove(&vm->arena[adr + i], &player->code[i], 1);
			ft_memmove(&vm->c_arena.color[(adr + i)], &player->color, 1);
		}
		i++;
	}
}

/*
** Sorts the players in the arena, from biggest to smallest by player_number.
*/

void				ft_sort_champ(t_vm *vm, int i, int j)
{
	while (i < vm->nbr_players)
	{
		j = 0;
		while (j < vm->nbr_players)
		{
			if (vm->player[i].number < vm->player[j].number && i != j)
				vm->player[i].index++;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < vm->nbr_players)
	{
		vm->player[i].address = vm->a[i];
		i++;
	}
}

/*
** Loads a fresh arena and positions the players, at cycle 0.
*/

void				load_arena(t_vm *vm)
{
	int i;

	i = 0;
	ft_bzero(vm->c_arena.color, sizeof(vm->c_arena.color));
	ft_bzero(vm->c_arena.pc, sizeof(vm->c_arena.pc));
	ft_bzero(vm->c_arena.lpc, sizeof(vm->c_arena.lpc));
	ft_bzero(vm->c_arena.lcolor, sizeof(vm->c_arena.lcolor));
	while (i < vm->nbr_players)
	{
		vm->player[i].color = i + 1;
		vm->c_arena.lpc[vm->player[i].address] += 1;
		vm->c_arena.pc[vm->player[i].address] = vm->player[i].color;
		vm->c_arena.lcolor[vm->player[i].address] = vm->player[i].color;
		load(vm, &vm->player[i], vm->player[i].address);
		i++;
	}
}
