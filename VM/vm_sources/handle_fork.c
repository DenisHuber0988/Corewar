/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:16:38 by aschukin          #+#    #+#             */
/*   Updated: 2018/09/27 17:53:09 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Supprime le fork qui n a pas fait d appel à Live et raccroche la liste
**	chainées correctement.
*/

static t_player		*delete_fork(t_vm *vm, t_player *tmp)
{
	t_player	*tmp_prev;

	if (vm->t == 4)
		ft_printf("A process belonging to %s has been killed at cycle [%d] !\n",
		tmp->name, vm->cycle);
	if (tmp == vm->fork)
	{
		vm->fork = vm->fork->next;
		ft_memdel((void**)&tmp);
		tmp = vm->fork;
	}
	else
	{
		tmp_prev = vm->fork;
		while (tmp_prev->next != tmp)
			tmp_prev = tmp_prev->next;
		tmp_prev->next = tmp->next;
		ft_memdel((void**)&tmp);
		tmp = tmp_prev;
	}
	return (tmp);
}

/*
**	Verifie la liste des forks encore en vie.
*/

void				ft_check_fork(t_vm *vm, t_player *fork)
{
	t_player	*tmp;

	tmp = fork;
	while (tmp)
	{
		if (!tmp->lives)
		{
			vm->nbr_fork -= 1;
			tmp = delete_fork(vm, tmp);
		}
		else
			tmp = tmp->next;
	}
}

/*
**	Execute les forks du plus jeune au plus vieux.
*/

void				do_fork(t_vm *vm, t_player *player)
{
	t_player	*fork;

	if (!player)
		return ;
	fork = player;
	while (fork)
	{
		if (fork->countdown == 1 && !fork->is_dead)
			exec_instruction(vm, fork, g_op_tab[fork->op - 1].ft_op);
		else if (!fork->instruction && !fork->is_dead)
			take_instruction(vm, fork);
		if (fork->instruction && fork->countdown != 1 && !fork->is_dead)
			fork->countdown--;
		fork = fork->next;
	}
}
