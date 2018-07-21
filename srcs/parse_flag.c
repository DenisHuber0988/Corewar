/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:00:13 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/21 16:50:06 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/virtual_machine.h"
#include <limits.h>

static int		check_load(int ref, int to_add)
{
	int	tmp;

	if (to_add + CHAMP_MAX_SIZE > MEM_SIZE)
	{
		tmp = (to_add + CHAMP_MAX_SIZE) - MEM_SIZE;
		if (ref <= tmp || ref >= to_add - CHAMP_MAX_SIZE)
			return (0);
	}
	else if (to_add - CHAMP_MAX_SIZE < 0)
	{
		tmp = (to_add - CHAMP_MAX_SIZE) + MEM_SIZE;
		if (ref >= tmp || ref <= to_add + CHAMP_MAX_SIZE)
			return (0);
	}
	else if (to_add + CHAMP_MAX_SIZE <= MEM_SIZE &&
			to_add - CHAMP_MAX_SIZE >= 0)
	{
		if (ref >= to_add + CHAMP_MAX_SIZE ||
				ref >= to_add - CHAMP_MAX_SIZE)
			return (0);
	}
	return (1);
}

static void		parse_a(t_vm *vm, char *av, int player)
{
	int	i;
	int	address;

	i = 0;
	if (!av || !*av)
		ft_error(vm, "Missing arg after flag -a.", "", 0);
	else if (my_isdigit(av))
	{
		address = my_atoll(av, vm) % MEM_SIZE;
		if (address < 0)
			address += MEM_SIZE;
		while (i < player)
		{
			if (!check_load(vm->a[i], address))
				ft_error(vm, "May overwrite another champ.", "", 1);
			i++;
		}
		vm->a[player] = address;
	}
	else
		ft_error(vm, "Non digit arg after flag -a. -> ", av, 0);
}

static void		parse_n(t_vm *vm, char *av, int player)
{
	int	i;

	i = 0;
	if (!av || !*av)
		ft_error(vm, "Missing arg after flag -n.", "", 0);
	else if (my_isdigit(av))
	{
		while (vm->n[i])
			if (vm->n[i++] == my_atoll(av, vm))
				ft_error(vm, "Same number for two champs -> ", av, 1);
		vm->n[player] = my_atoll(av, vm);
	}
	else
		ft_error(vm, "Non digit after flag -n -> ", av, 1);
}

static void		parse_dump(t_vm *vm, char *av)
{
	if (!av || !*av)
		ft_error(vm, "Missing arg after flag -dump.", "", 0);
	else if (my_isdigit(av))
	{
		if (my_atoll(av, vm) >= 0 && my_atoll(av, vm) < INT_MAX)
			vm->dump = my_atoll(av, vm);
		else if (my_atoll(av, vm) < 0)
			ft_error(vm, "Need a positive number for dump.", "", 0);
	}
	else
		ft_error(vm, "Non digit arg after flag -dump.", av, 0);
}

void			parse_flag(t_vm *vm)
{
	vm->av += 1;
	while (*vm->av)
	{
		if (ft_strstr(*vm->av, "."))
			valid_extension(vm, *(vm->av));
		if (!ft_strcmp(*vm->av, "-v"))
			vm->v = 1;
		if (!ft_strcmp(*vm->av, "-dump"))
			parse_dump(vm, *(vm->av + 1));
		else if (!ft_strcmp(*vm->av, "-n"))
			parse_n(vm, *(vm->av + 1), vm->nbr_players);
		else if (!ft_strcmp(*vm->av, "-a"))
			parse_a(vm, *(vm->av + 1), vm->nbr_players);
		else
			unknown_instruction(vm, *(vm->av), *(vm->av + 1));
		vm->av += 1;
	}
	if (vm->nbr_players == 0)
		ft_error(vm, "Need at least one champ.", "", 0);
	else if (vm->nbr_players > 4)
		ft_error(vm, "Max four champs.", "", 1);
}
