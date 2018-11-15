/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 13:11:46 by mkamel            #+#    #+#             */
/*   Updated: 2018/09/25 19:36:35 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	In the case of several players being called:
**	the int 'j' will be the number of addresses given with the flag -a.
**
**	IF j == 0, then we just divide the arena memory by the number of players
**	to obtain their adress : " i * (MEM_SIZE / NB_PLAYERS) ".
**
**	ELSE:
**	ft_check_ad will give the right address to the different players, separating
**	them with as much space as possible.
*/

void		ft_deal_two_pl(t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != 2)
		if (vm->a[i++] != -1)
			j++;
	i = 0;
	while (i != 2 && j != 2)
	{
		if (vm->a[i] == -1)
		{
			j == 0 ? vm->a[i] = (i * (MEM_SIZE / 2)) : ft_check_ad(vm, 2, j);
			j++;
		}
		i++;
	}
}

void		ft_deal_three_pl(t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != 3)
		if (vm->a[i++] != -1)
			j++;
	i = 0;
	while (i != 3 && j != 3)
	{
		if (vm->a[i] == -1)
		{
			j == 0 ? vm->a[i] = (i * (MEM_SIZE / 3)) : ft_check_ad(vm, 3, j);
			if (j != 0)
				break ;
		}
		i++;
	}
}

void		ft_deal_four_pl(t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != 4 && j != 4)
		if (vm->a[i++] != -1)
			j++;
	i = 0;
	while (i != 4 && j != 4)
	{
		if (vm->a[i] == -1)
		{
			j == 0 ? vm->a[i] = (i * (MEM_SIZE / 4)) : ft_check_ad(vm, 4, j);
			if (j != 0)
				break ;
		}
		i++;
	}
}

/*
**	Define the previously determined address in each player structure.
*/

void		ft_give_address(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nbr_players)
	{
		vm->player[i].address = vm->a[i];
		i++;
	}
}

/*
**	Deals with the different possibilities allowed by the flag -a through
**	speficic functions (deal_two, deal_three,...) to define the adress for
**	every player.
*/

void		ft_place_champ(t_vm *vm)
{
	if (vm->nbr_players == 1)
		vm->a[0] == -1 ? vm->a[0] = 0 : 0;
	else if (vm->nbr_players == 2)
		ft_deal_two_pl(vm);
	else if (vm->nbr_players == 3)
		ft_deal_three_pl(vm);
	else if (vm->nbr_players == 4)
		ft_deal_four_pl(vm);
	ft_give_address(vm);
}
