/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:40:45 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/22 17:50:41 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#include "../vm_includes/printer.h"

/*
**	Print_visu is the main function used by our visualizer.
**
**	It first print an esthetic header, that is decomposed in the different T'x'.
**	This division was required by our norm characters limit per line.
**	Then we print the arena per se, with the print_arena function,
**	and finally the main infos of every cycle.
*/

void		print_visu(t_vm *vm, int i)
{
	ft_printf("\x1b[?25l");
	ft_printf("%s\n%s%s%s%s%s\n%s%s%s%s\n", CLEAR, COLOR, \
			T0, T1, T2, T3, T00, T01, T02, T03);
	ft_printf("%s%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n", COLOR_2, \
			T10, T11, T12, T20, T21, T22, T30, T31, T32, T40, T41, T42);
	ft_printf("%s%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s%s\n%s%s%s%s\n", COLOR_3, \
			T50, T51, T52, T60, T61, T62, T70, T71, T72, \
			T00, T01, T02, T03, T0, T1, T2, T3);
	ft_printf("%s\n", DEFAULT);
	print_arena(vm);
	ft_printf("\nCycle = [%7.7d]\n", (!vm->cycle) ? 0 : vm->cycle - 1);
	ft_printf("Cycle to die = [%7.7d]\n", vm->cycles_to_die);
	ft_printf("Check = [%7.7d]\n", vm->check);
	ft_printf("\nProcess alive = [%6.6d]\n", vm->nbr_process);
	ft_printf("Players alive = [%1.d]\n", vm->players_alive);
	ft_printf("\nLive calls in the Revolution = [%6.6d]\n", vm->nbr_live);
	ft_printf("%c[2KLast live is from player %s.\n", 27, vm->winner_name);
	vm->taunt[0] ? ft_printf("Player [%s] n°[%d] says at cycle [%d]: '%s' !\n",
				vm->taunt_name, vm->taunt_nb, vm->taunt_cycle, vm->taunt) : 0;
	while (++i < vm->nbr_players)
		(!vm->player[i].is_dead) ? ft_printf("%c[2K%s is alive with %d lives\n",
		27, vm->player[i].name, vm->player[i].lives_p) : ft_printf("\x1b[?25l");
	(vm->p >= 0) ? usleep(100000 * (vm->p % 10)) : 0;
}

/*
**	Deal_pc enables to highlight a VM case if there is a process on it.
*/

void		deal_pc(t_vm *vm, int i)
{
	if (vm->c_arena.pc[i] == 1)
		(vm->c_arena.color[i] = 11);
	else if (vm->c_arena.pc[i] == 2)
		(vm->c_arena.color[i] = 12);
	else if (vm->c_arena.pc[i] == 3)
		(vm->c_arena.color[i] = 13);
	else if (vm->c_arena.pc[i] == 4)
		(vm->c_arena.color[i] = 14);
}

/*
**	Print_color enables to color a VM case with the corresponding player's
**	color. If there is no player, then it's printed in white.
*/

void		print_color(t_vm *vm, int i)
{
	if (vm->c_arena.color[i] == 10)
		ft_printf(BG_WHI);
	else if (vm->c_arena.color[i] == 11)
		ft_printf(BG_RED);
	else if (vm->c_arena.color[i] == 12)
		ft_printf(BG_GRE);
	else if (vm->c_arena.color[i] == 13)
		ft_printf(BG_YEL);
	else if (vm->c_arena.color[i] == 14)
		ft_printf(BG_BLU);
	else if (vm->c_arena.color[i] == 0)
		ft_printf(DEFAULT);
	else if (vm->c_arena.color[i] == 1)
		ft_printf(RED);
	else if (vm->c_arena.color[i] == 2)
		ft_printf(GRE);
	else if (vm->c_arena.color[i] == 3)
		ft_printf(YEL);
	else if (vm->c_arena.color[i] == 4)
		ft_printf(BLU);
}

/*
**	Print_arena is an iterative loop printing every case of the VM one by one.
**
**	First it deals with the PC or the player's code color,
**	then it actually prints the character in the VM case, puts back the color
**	to DEFAULT, and finally print either a '\n' or a ' ' to separate every case.
*/

void		print_arena(t_vm *vm)
{
	int		i;
	char	c;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->c_arena.lpc[i])
			deal_pc(vm, i);
		print_color(vm, i);
		if (!((i + 1) % 64) && i)
			c = '\n';
		else
			c = ' ';
		ft_printf("%.2x%s%c", vm->arena[i++], DEFAULT, c);
	}
}

/*
**	Print_vm displays the initial states of the VM and the players infos.
**
**	THE COLOR_ARENA STRUCTURE
**	Works like 4 tracing papers applied on the VM_ARENA, allowing to know :
**		- The color of the memory case you're on (int color[]);
**		- The presence of a pc and the color of its player (int pc[]);
**		- The Number of pc there are at the same time on the case (lpc[]);
**		- The last color of the case, before any PC passed on it (lcolor[]);
**
**	typedef struct		s_col_arena
**	{
**		int				color[MEM_SIZE + 1];
**		int				pc[MEM_SIZE + 1];
**		int				lpc[MEM_SIZE + 1];
**		int				lcolor[MEM_SIZE + 1];
**	}					t_col_arena;
*/

void		print_vm(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("Introducing the champions :\n");
	while (i < vm->nbr_players)
	{
		ft_printf("player %d = [%d]\n", i + 1, vm->player[i].number);
		ft_printf("player->index = [%d]\n", vm->player[i].index);
		ft_printf("player name = [%s]\n", vm->player[i].name);
		ft_printf("player address = [%d]\n\n", vm->player[i].address);
		ft_printf("program size = [%d]\n", vm->player[i].program_size);
		ft_printf("comment = [%s]\n", vm->player[i].comment);
		ft_printf("\n\t\t-----------------------------\n");
		i++;
	}
	ft_printf(CLEAR2);
}
