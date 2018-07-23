/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:00:13 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/23 15:48:51 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#include <limits.h>

static int		check_load(int ref, int to_add)
{
	int	tmp;

	if (ref > to_add)
		ft_swap(&ref, &to_add);
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
		if (vm->a[player] < 0)
			vm->a[player] += MEM_SIZE;
		while (i < player)
			if (!check_load(vm->a[i++], vm->a[player]))
				vm_error(vm, "May overwrite another champ.", "", 1);
	}
	else
		vm_error(vm, "Non digit arg after flag -a. -> ", av, 0);
}

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
		while (vm->n[i])
			if (vm->n[i++] == vm_atoll(av, vm))
				vm_error(vm, "Same number for two champs -> ", av, 1);
		vm->n[player] = vm_atoll(av, vm);
	}
	else
		vm_error(vm, "Non digit after flag -n -> ", av, 1);
}

static void		parse_dump(t_vm *vm, char *av)
{
	if (!av || !*av)
		vm_error(vm, "Missing arg after flag -dump.", "", 0);
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

void			parse_flag(t_vm *vm)
{
	char	**tmp;

	tmp = (vm->av + 1);
	while (*tmp)
	{
		if (ft_strstr(*tmp, "."))
			valid_extension(vm, *(tmp));
		if (!ft_strcmp(*vm->av, "-v"))
			vm->v = 1;
		if (!ft_strcmp(*tmp, "-dump"))
			parse_dump(vm, *(tmp + 1));
		else if (!ft_strcmp(*tmp, "-n"))
			parse_n(vm, *(tmp + 1), tmp, vm->nbr_players);
		else if (!ft_strcmp(*tmp, "-a"))
			parse_a(vm, *(tmp + 1), tmp, vm->nbr_players);
		else
			unknown_instruction(vm, *(tmp), *(tmp + 1));
		tmp += 1;
	}
	if (vm->nbr_players == 0)
		vm_error(vm, "Need at least one champ.", "", 0);
	else if (vm->nbr_players > 4)
		vm_error(vm, "Max four champs.", "", 1);
}
