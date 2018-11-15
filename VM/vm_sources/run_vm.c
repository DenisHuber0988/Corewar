/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:29:29 by mkamel            #+#    #+#             */
/*   Updated: 2018/10/05 17:17:25 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** After an instruction is read, it must wait N cycles (tmp->countdown) before
** it is executed. The number of cycles for each move is defined in op.c.
**
** IF an instruction has been read and tmp->countdown has been reached,
** the instruction is executed.
** ELSE IF no instruction has been read and the player is still alive,
** the next instruction is read.
** IF tmp->countdown has not been reached, it is decremented.
**
** Players may die waiting for their instructions to be executed.
*/

static void		play(t_vm *vm, int x, int *i, int ind)
{
	t_player	*tmp;

	vm->players_alive = 0;
	while (ind <= vm->nbr_players)
	{
		while (vm->player[x].index != ind)
			x++;
		tmp = &vm->player[x];
		if (tmp->countdown == 1 && !tmp->is_dead)
			exec_instruction(vm, tmp, g_op_tab[tmp->op - 1].ft_op);
		else if (!tmp->instruction && !tmp->is_dead)
			take_instruction(vm, tmp);
		if (tmp->instruction && tmp->countdown != 1 && !tmp->is_dead)
			vm->player[x].countdown--;
		vm->nbr_process += (!tmp->is_dead) ? 1 : 0;
		vm->players_alive += (!tmp->is_dead) ? 1 : 0;
		x = 0;
		ind++;
	}
	*i += 1;
}

/*
** If dump or -s flag, displays the arena.
** Executes player and fork processes, until CYCLES_TO_DIE has been reached.
** Processes are executed in order of youth (forks are executed before players).
** do_fork : executes fork process, or moves.
** play : executes player proccess, or moves.
*/

static void		ft_revolution(t_vm *vm, int i)
{
	if (vm->dump == vm->cycle)
	{
		dump_memory(vm, 0);
		return ;
	}
	if ((vm->s > 0 && vm->cycle > 0) && !(vm->cycle % vm->s))
		dump_memory_s(vm, 0);
	if (i < vm->cycles_to_die)
	{
		if (vm->v >= 0 && vm->v <= vm->cycle)
			print_visu(vm, -1);
		vm->cycle++;
		vm->nbr_process = 0;
		do_fork(vm, vm->fork);
		play(vm, 0, &i, 1);
		vm->nbr_process += vm->nbr_fork;
		ft_revolution(vm, i);
	}
}

/*
** Resets each player's and their fork's stats (number of 'lives' called)
** to zero, at the end of each revolution.
*/

static void		ft_reset(t_vm *vm, int i)
{
	t_player	*tmp;
	int			x;
	int			live;

	vm->nbr_live = 0;
	vm->nbr_process = 0;
	live = 0;
	while (i < vm->nbr_players)
	{
		tmp = &vm->player[i++];
		(tmp->lives) ? live++ : 0;
		tmp->lives = 0;
		tmp->lives_p = 0;
	}
	tmp = vm->fork;
	x = vm->nbr_fork;
	while (tmp || x)
	{
		tmp->lives = 0;
		tmp->lives_p = 0;
		tmp = tmp->next;
		x--;
	}
	vm->nbr_process = vm->nbr_fork + live;
}

/*
** Checks to see if the player has called 'live' during the last revolution.
** If they have not, that player is considered dead.
*/

static void		ft_check_champ(t_vm *vm, int i)
{
	t_player	*player;

	if (i < vm->nbr_players)
	{
		player = &vm->player[i];
		if (player->lives == 0)
			player->is_dead = 1;
		if (!player->is_dead)
			vm->players_alive++;
		ft_check_champ(vm, ++i);
	}
}

/*
** EXECUTES THE GAME
** (i.e. the player processes, as they battle to the death in the arena).
** One revolution is the number of turns until CYCLES_TO_DIE is reached.
**
** ft_revolution : executes player and fork processes for one revolution.
** ft_check_fork : checks if forks have called 'live' during last revolution.
** ft_check_champ : checks if players have called 'live' during last revolution.
** ft_reset : once CYCLES_TO_DIE is reached, any player that has not called
**	'live' is considered 'dead' and the remaining player 'lives' are reset to 0.
*/

void			run_vm(t_vm *vm)
{
	if (vm->v >= 0 && vm->m)
		system("afplay MP3/Debug.mp3 &");
	while (vm->cycles_to_die > 0)
	{
		vm->nbr_process = vm->nbr_players;
		ft_revolution(vm, 0);
		vm->players_alive = 0;
		ft_check_fork(vm, vm->fork);
		ft_check_champ(vm, 0);
		if ((vm->players_alive <= 1 && vm->h) || !vm->dump || !vm->nbr_live)
			return ;
		if (vm->nbr_live >= NBR_LIVE || vm->check == MAX_CHECKS)
		{
			vm->cycles_to_die -= CYCLE_DELTA;
			vm->check = 0;
			vm->nbr_live = 0;
		}
		else
			vm->check++;
		ft_reset(vm, 0);
	}
}
