/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:00:13 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 17:12:12 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Parse the arguments to check if the -a flag is used.
**	The -a flag allows to choose a specific address for a champ.
**
**	1) Check that there is a .cor file after the flag is used.
**	2) Check there are info after the flag.
**	3) Check the info is a valid integer.
**	4) Check that the adress given won't write on another player's code.
**
**	If the flag is used several times, the latest address value is used.
*/

static void		parse_a(t_vm *vm, char *av, char **check, int player)
{
	int	i;

	i = 0;
	while (*check)
	{
		if (ft_strstr(*check, ".cor"))
			i = 1;
		check += 1;
	}
	if (!i)
		vm_error(vm, "Missing champ after flag -a.", "", 0);
	i = 0;
	if (!av || !*av)
		vm_error(vm, "Missing arg after flag -a.", "", 0);
	else if (vm_isdigit(av))
	{
		vm->a[player] = vm_atoll(av, vm) % MEM_SIZE;
		if (vm_atoll(av, vm) < 0)
			vm_error(vm, "Flag -a needs a positive address.", "", 1);
		while (i < player)
			if (!check_load(vm->a[i++], vm->a[player]))
				vm_error(vm, "May overwrite another champ.", "", 1);
	}
	else
		vm_error(vm, "Non digit arg after flag -a. -> ", av, 0);
}

/*
**	Parse the arguments to check if the -n flag is used.
**	The -n flag allows to choose a specific player_number for a champ.
**
**	1) Check that there is a .cor file after the flag is used.
**	2) Check there are info after the flag.
**	3) Check the info is a valid integer.
**	4) Check that the number given is not used twice.
**
**	If the flag is used several times, the latest number value is used.
*/

static void		parse_n(t_vm *vm, char *av, char **check, int player)
{
	int	i;

	i = 0;
	while (*check)
	{
		if (ft_strstr(*check, ".cor"))
			i = 1;
		check += 1;
	}
	if (!i)
		vm_error(vm, "Missing champ after flag -n.", "", 0);
	i = 0;
	if (!av || !*av)
		vm_error(vm, "Missing arg after flag -n.", "", 0);
	else if (vm_isdigit(av))
	{
		while (i < player)
		{
			if (vm->n[i++] == vm_atoll(av, vm))
				vm_error(vm, "Same number for two champs -> ", av, 1);
		}
		vm->n[player] = vm_atoll(av, vm);
	}
	else
		vm_error(vm, "Non digit after flag -n -> ", av, 1);
}

/*
**	Parse the arguments to check if the -dump flag is used.
**	The -dump flag allows to print the memory state at a specific cycle number.
**
**	1) Check there are info after the flag.
**	2) Check the info is a valid integer.
**
**	If the flag is used several times, the latest dump value is used.
*/

static void		parse_dump(t_vm *vm, char *av)
{
	if (!av || !*av)
		vm_error(vm, "Missing int arg after flag -dump.", "", 0);
	else if (vm_isdigit(av))
	{
		if (vm_atoll(av, vm) >= 0 && vm_atoll(av, vm) < INT_MAX)
			vm->dump = vm_atoll(av, vm);
		else if (vm_atoll(av, vm) < 0)
			vm_error(vm, "Need a positive number for dump.", "", 0);
	}
	else
		vm_error(vm, "Non digit arg after flag -dump.", av, 0);
}

/*
** The function has the same architecture as the -dump one.
*/

static void		parse_v(t_vm *vm, char *av)
{
	if (!av || !*av)
		vm_error(vm, "Missing int arg after flag -v.", "", 0);
	else if (vm_isdigit(av))
	{
		if (vm_atoll(av, vm) >= 0 && vm_atoll(av, vm) < INT_MAX)
			vm->v = vm_atoll(av, vm);
		else if (vm_atoll(av, vm) < 0)
			vm_error(vm, "Need a positive number for flag -v.", "", 0);
	}
	else
		vm_error(vm, "Non digit arg after flag -v.", av, 0);
}

/*
** Parses for valid files (ending in .cor),
** as well as the following flags :
**	MANDATORY FLAGS :
** 		-dump: dumps memory after N cycles.
** 		-n : gives the number N to a player
**	BONUS FLAGS :
** 		-v : launches the visualizer/debugger at cycle N.
** 		-a : places a player at address N % MEM_SIZE
**		 -s : runs N cycles, dumps memory, pauses, then repeats.
** 		-p : sets the pace of the debugger at N % 10.
** 		-t : displays textual information.
**
** If invalid files or the number of players is > 4, an error message is given.
*/

void			parse_flag(t_vm *vm, char **tmp)
{
	tmp = (vm->av + 1);
	vm_isdigit(*tmp) ? vm_error(vm, "Expect a flag before number.", "", 1) : 0;
	while (*tmp)
	{
		if (ft_strstr(*tmp, ".cor"))
			vm->cor++;
		if (ft_strstr(*tmp, "."))
			valid_extension(vm, *(tmp));
		if (!ft_strcmp(*tmp, "-v"))
			parse_v(vm, *(tmp + 1));
		if (!ft_strcmp(*tmp, "-dump"))
			parse_dump(vm, *(tmp + 1));
		else if (!ft_strcmp(*tmp, "-n"))
			parse_n(vm, *(tmp + 1), tmp, vm->nbr_players);
		else if (!ft_strcmp(*tmp, "-a"))
			parse_a(vm, *(tmp + 1), tmp, vm->nbr_players);
		else if (!ft_strcmp(*tmp, "-p") || !ft_strcmp(*tmp, "-s") \
				|| !ft_strcmp(*tmp, "-t") || !ft_strcmp(*tmp, "-h") \
				|| !ft_strcmp(*tmp, "-m"))
			parse_flag2(vm);
		else
			unknown_instruction(vm, *(tmp), *(tmp + 1));
		tmp += 1;
		(vm->cor > 4) ? vm_error(vm, "Max four champs.", "", 1) : 0;
	}
}
