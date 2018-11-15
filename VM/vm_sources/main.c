/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:16:02 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 16:49:31 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

void		print_winner_color(t_vm *vm)
{
	if (vm->last_color == 1)
		ft_printf(RED);
	else if (vm->last_color == 2)
		ft_printf(GRE);
	else if (vm->last_color == 3)
		ft_printf(YEL);
	else if (vm->last_color == 4)
		ft_printf(BLU);
}

void		declare_winner(t_vm *vm)
{
	if (vm->v >= 0 && vm->m)
		system("killall afplay");
	if (vm->last_live == 0)
	{
		ft_printf("\n\n\t\t\t");
		ft_printf("ZERO CALL TO LIVE.\n\t\t\t\x1b[1;3;31m NO WINNER\x1b[0m\n");
		usleep(800000);
		system("afplay MP3/End2.mp3 &");
	}
	else
	{
		ft_printf("\n\nAnd the winner is after %d cycles...\n\n", vm->cycle);
		usleep(800000);
		usleep(800000);
		system("afplay MP3/End.mp3 &");
		print_winner_color(vm);
		ft_printf("\t\t\tPlayer n°[%d] : \x1b[1;3;m %s\x1b[0m\n\n",
				vm->last_live, vm->winner_name);
	}
}

void		usage(void)
{
	ft_printf("Usage : ./corewar ");
	ft_printf("[-dump N | -n N | -a N | -v N] <champion1.cor> <...>\n\n");
	ft_printf("#### MANDATORY PART ####################################\n");
	ft_printf("\t-dump N\t\t: Dumps memory after N cycles.\n");
	ft_printf("\t-n N\t\t: Gives the number N to the champion.\n\n");
	ft_printf("#### BONUS #############################################\n");
	ft_printf("\t-a N\t\t: Gives the address N %% MEM_SIZE to the champion.\n");
	ft_printf("\t-s N\t\t: Runs N cycles, dumps memory, pauses, then repeats.");
	ft_printf("\n\n\t-t N\t\t: Textual Informations.\n");
	ft_printf("\t\t\t\t\t- 1 : Show only essentials.\n");
	ft_printf("\t\t\t\t\t- 2 : Show calls to live.\n");
	ft_printf("\t\t\t\t\t- 4 : Show process dying.\n");
	ft_printf("\t-h N\t\t: Hardcore Mode On. The party ends if a player\n\t\
		doesn't say live during Cycles_to_die\n");
	ft_printf("#### VISUAL OUTPUT MODE ################################\n");
	ft_printf("\t-v N\t\t: Launch the visual debugger at the cycle N.\n");
	ft_printf("\t-p N\t\t: Set the pace of the debugger at  N %% 10.\n");
	ft_printf("#### MUSICAL MODE ################################\n");
	ft_printf("\t-m : Plays a background music for the debugger\n");
	exit(1);
}

void		free_all(t_vm *vm)
{
	t_player *tmp;

	if (!vm->fork || !vm->nbr_fork)
		return ;
	tmp = vm->fork;
	while (tmp)
	{
		tmp = vm->fork->next;
		ft_memdel((void**)&(vm->fork));
		vm->fork = tmp;
	}
}

/*
** The main does the following:
** 1) if no arguments: displays usage
** 2) init : initalizes the virtual arena of memory
** 3) parse_flag & setting_vm : parses for flags and activates them in vm_struct
** 4) parse_champ : parses + stores each player in an array of structs
** 5) ft_sort_champ : sorts players from biggest to smallest by player_number
** 6) print_vm : displays the initial values of the players
** 7) load_arena : puts in place the arena + players, at cycle 0
** 8) run_vm : executes the game (displays arena at every cycle, if -v flag)
** 9) free_all : frees all malloc'ed player forks
** 10) dump : displays the arena at _x_ memory cycle
** 11) A winner is declared!
** Game over.
*/

int			main(int ac, char **av)
{
	t_vm		vm;
	char		*tmp;

	if (ac == 1)
		usage();
	init(&vm, ac, av);
	parse_flag(&vm, &tmp);
	setting_vm(&vm);
	parse_champ(&vm);
	ft_sort_champ(&vm, 0, 0);
	print_vm(&vm);
	load_arena(&vm);
	run_vm(&vm);
	free_all(&vm);
	if (vm.dump > 0)
		dump(&vm, 0);
	else
		declare_winner(&vm);
	return (0);
}
