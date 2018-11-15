/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:24:48 by dhuber            #+#    #+#             */
/*   Updated: 2018/09/25 18:00:21 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** FORK
** Takes an index and creates a new process which is
** executed from address: (PC + (first parameter % IDX_MOD)).
** This process inherits all of its parent's states.
** Forked processes are stored in a linked list, at vm->player[i]->next.
** Each player has its own linked list of forks.
*/

static void		init_part2(t_vm *vm, t_player *player, t_player *fork)
{
	int i;

	i = 0;
	while (i < 16)
	{
		fork->reg[i] = player->reg[i];
		i++;
	}
	vm->c_arena.lpc[(fork->address + fork->pc) % MEM_SIZE] += 1;
	if (vm->c_arena.lpc[(fork->address + fork->pc) % MEM_SIZE] == 1)
		vm->c_arena.lcolor[(fork->address + fork->pc) % MEM_SIZE] =
			vm->c_arena.color[(fork->address + fork->pc) % MEM_SIZE];
	vm->c_arena.pc[(fork->address + fork->pc) % MEM_SIZE] = fork->color;
}

static void		init_fork(t_vm *vm, t_player *player, t_player *fork, short adr)
{
	ft_memcpy(fork->name, player->name, PROG_NAME_LENGTH + 1);
	ft_memcpy(fork->comment, player->comment, COMMENT_LENGTH + 1);
	ft_memcpy(fork->code, player->code, CHAMP_MAX_SIZE + 1);
	ft_memcpy(fork->taunt, player->taunt, AFF_MAX + 1);
	fork->program_size = player->program_size;
	fork->number = player->number;
	fork->address = player->address;
	fork->lives = player->lives;
	fork->carry = player->carry;
	fork->pc = adr;
	fork->tmpc = fork->pc;
	fork->op = player->op;
	fork->is_opc = 0;
	fork->is_dead = 0;
	fork->instruction = 0;
	fork->countdown = 0;
	fork->index_aff = player->index_aff;
	fork->color = player->color;
	fork->next = (vm->fork) ? vm->fork : NULL;
	init_part2(vm, player, fork);
}

static void		add_fork(t_vm *vm, t_player *player, short adr)
{
	t_player	*tmp;
	t_player	*fork;

	tmp = player;
	if (!(fork = (t_player *)ft_memalloc(sizeof(t_player))))
		vm_error(vm, "Not enough memory to fork : ", player->name, 1);
	init_fork(vm, player, fork, adr);
	vm->fork = fork;
	tmp = vm->fork;
}

static short	recup(t_vm *vm, t_player *player, short adr)
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
	player->tmpc += 2;
	return (final_adr);
}

int				op_fork(t_vm *vm, t_player *player, int *arg)
{
	short		adr;

	arg[0] = recup(vm, player, (player->address + player->pc + 1) % MEM_SIZE);
	adr = (player->pc + ((short)arg[0] % IDX_MOD)) % MEM_SIZE;
	add_fork(vm, player, adr);
	vm->nbr_fork += 1;
	move_pc(vm, player);
	if (vm->t == 1)
		ft_printf("%s executes successfully a fork at cycle [%d].\n",
		player->name, vm->cycle);
	return (OP_SUCCESS);
}
