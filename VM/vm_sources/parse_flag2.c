/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:02:26 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 17:22:54 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Setting_vm manages the priority between different flags
**	that could interfere as follow :
**		-dump	>>	-s	>>	-t	>>	-p	>>	-v
*/

void			setting_vm(t_vm *vm)
{
	if (vm->p >= 0)
		if (vm->v == -1)
			vm->v = 0;
	if (vm->t > 0)
		vm->v = -1;
	if (vm->s > 0)
	{
		vm->t = -1;
		vm->v = -1;
	}
	if (vm->dump > 0)
	{
		vm->s = -1;
		vm->v = -1;
		vm->t = -1;
	}
}

/*
**	Parse the arguments to check if the -s flag is used.
**	The -s flag allows to dump the memory state every cycle number specified.
**
**	1) Check there are info after the flag.
**	2) Check the info is a valid integer.
**
**	If the flag is used several times, the latest dump value is used.
*/

static void		parse_s(t_vm *vm, char *av)
{
	if (!av || !*av)
		vm_error(vm, "Missing int arg after flag -s.", "", 0);
	else if (vm_isdigit(av))
	{
		if (vm_atoll(av, vm) >= 0 && vm_atoll(av, vm) < INT_MAX)
			vm->s = vm_atoll(av, vm);
		else if (vm_atoll(av, vm) < 0)
			vm_error(vm, "Need a positive number for -s.", "", 0);
	}
	else
		vm_error(vm, "Non digit arg after flag -s.", av, 0);
}

/*
**	Parse the arguments to check if the -p flag is used.
**	The -p flag allows to print the memory at a specified pace.
**
**	1) Check there are info after the flag.
**	2) Check the info is a valid integer.
**
**	If the flag is used several times, the latest dump value is used.
*/

static void		parse_p(t_vm *vm, char *av)
{
	if (!av || !*av)
		vm_error(vm, "Missing int arg after flag -p.", "", 0);
	else if (vm_isdigit(av))
	{
		if (vm_atoll(av, vm) >= 0 && vm_atoll(av, vm) <= INT_MAX)
			vm->p = vm_atoll(av, vm);
		else if (vm_atoll(av, vm) < 0)
			vm_error(vm, "Need a positive number for -p.", "", 0);
	}
	else
		vm_error(vm, "Non digit arg after flag -p.", av, 0);
}

/*
**	Parse the arguments to check if the -t flag is used.
**	The -t flag allows to print the action that occured during the game.
**
**	1) Check there are info after the flag.
**	2) Check the info is a valid integer.
**
**	If the flag is used several times, the latest dump value is used.
*/

static void		parse_t(t_vm *vm, char *av)
{
	if (!av || !*av)
		vm_error(vm, "Missing int arg after flag -t.", "", 0);
	else if (vm_isdigit(av))
	{
		if (vm_atoll(av, vm) >= 0 && vm_atoll(av, vm) < INT_MAX)
			vm->t = vm_atoll(av, vm);
		else if (vm_atoll(av, vm) < 0)
			vm_error(vm, "Need a positive number for -t.", "", 0);
	}
	else
		vm_error(vm, "Non digit arg after flag -t.", av, 0);
	if (vm->t != 1 && vm->t != 2 && vm->t != 4)
		vm_error(vm, "Waiting for 1 2 or 4 after flag -t.", av, 0);
}

/*
** Simply the following of parse_flag.
*/

void			parse_flag2(t_vm *vm)
{
	char	**tmp;

	tmp = (vm->av);
	while (*tmp)
	{
		if (!ft_strcmp(*tmp, "-p"))
			parse_p(vm, *(tmp + 1));
		if (!ft_strcmp(*tmp, "-s"))
			parse_s(vm, *(tmp + 1));
		if (!ft_strcmp(*tmp, "-t"))
			parse_t(vm, *(tmp + 1));
		if (!ft_strcmp(*tmp, "-h"))
			vm->h = 1;
		if (!ft_strcmp(*tmp, "-m"))
			vm->m = 1;
		tmp += 1;
	}
}
