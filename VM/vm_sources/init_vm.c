/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:03:16 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 16:55:01 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** Verifies that no two players share the same player number.
** In case of duplicates, player number is incremented.
*/

static void		recheck(t_vm *vm, t_player *player, int index, int i)
{
	while (i < vm->nbr_players)
	{
		if (vm->player[i].number == player->number && i != index)
		{
			player->number += 1;
			i = 0;
		}
		i++;
	}
}

/*
** Assigns a specific player_number to each player.
*/

static void		give_nbr(t_vm *vm, t_player *player, int nb, int index)
{
	int i;

	i = 0;
	if (!index)
		while (i < vm->nbr_players)
			vm->player[i++].number = 0;
	i = 0;
	while (i < vm->nbr_players)
	{
		if ((vm->n[i] == nb || vm->player[i].number == nb) && i != index)
		{
			nb++;
			i = 0;
		}
		i++;
	}
	player->number = nb;
	recheck(vm, player, index, 0);
}

/*
** Initializes the players.
*/

void			init_champ(t_vm *vm, t_player *player, int i)
{
	ft_memset(player->name, 0, PROG_NAME_LENGTH + 1);
	ft_memset(player->comment, 0, COMMENT_LENGTH + 1);
	ft_memset(player->reg, 0, sizeof(player->reg));
	ft_memset(player->arg, 0, sizeof(player->arg));
	ft_memset(player->type, 0, sizeof(player->type));
	ft_memset(player->code, 0, CHAMP_MAX_SIZE + 1);
	ft_memset(player->taunt, 0, AFF_MAX + 1);
	player->number = vm->n[i];
	if (vm->n[i] == 0)
		give_nbr(vm, player, i + 1, i);
	player->program_size = 0;
	player->address = vm->a[i];
	player->reg[0] = player->number;
	player->lives = 0;
	player->lives_p = 0;
	player->index = 1;
	player->is_dead = 0;
	player->carry = 0;
	player->pc = 0;
	player->tmpc = 0;
	player->op = 0;
	player->instruction = 0;
	player->countdown = 0;
	player->index_aff = 0;
	player->next = NULL;
}

/*
** Continuation of init.
** a flag: places player at a specific address in memory.
** n flag: gives a player a specific player_number.
*/

static void		init2(t_vm *vm)
{
	ft_memset(vm->winner_name, 0, PROG_NAME_LENGTH + 1);
	ft_memset(vm->taunt_name, 0, PROG_NAME_LENGTH + 1);
	ft_memset(vm->taunt, 0, AFF_MAX + 1);
	ft_memset(vm->n, 0, sizeof(vm->n));
	ft_memset(vm->a, -1, sizeof(vm->a));
	ft_memset(vm->arena, 0, MEM_SIZE + 1);
	ft_memset(vm->c_arena.color, 0, sizeof(vm->c_arena.color));
	ft_memset(vm->c_arena.lcolor, 0, sizeof(vm->c_arena.lcolor));
	ft_memset(vm->c_arena.lpc, 0, sizeof(vm->c_arena.lpc));
	ft_memset(vm->c_arena.pc, 0, sizeof(vm->c_arena.pc));
}

/*
** All game details are stored in the struct vm.
** Flags include: p, s, v, t, dump.
*/

void			init(t_vm *vm, int ac, char **av)
{
	vm->av = av;
	vm->ac = ac;
	vm->cor = 0;
	vm->p = -1;
	vm->s = -1;
	vm->v = -1;
	vm->t = -1;
	vm->h = 0;
	vm->m = 0;
	vm->cursors = 0;
	vm->dump = -1;
	vm->cycle = 0;
	vm->nbr_players = 0;
	vm->nbr_fork = 0;
	vm->nbr_process = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->check = 0;
	vm->nbr_live = 0;
	vm->players_alive = 0;
	vm->last_live = 0;
	vm->last_color = 0;
	vm->fork = NULL;
	vm->taunt_cycle = 0;
	vm->taunt_nb = 0;
	init2(vm);
}
