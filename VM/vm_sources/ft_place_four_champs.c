/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_four_champs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 19:09:57 by mkamel            #+#    #+#             */
/*   Updated: 2018/09/25 21:55:43 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#define MIN_3 ((address[0] < address[1]) ? address[0] : address[1])
#define MAX_3 ((address[0] > address[1]) ? address[0] : address[1])
#define MID_3 (MAX_3 - MIN_3)
#define MAD_4 ((MAX_3 + ((MEM_SIZE - MAX_3 + MIN_3) / 3)) % MEM_SIZE)
#define MAD_5 ((address[2] + ((MEM_SIZE - MAX_3 + MIN_3) / 3)) % MEM_SIZE)
#define D_1 (dist_tab[0])
#define D_2 (dist_tab[1])
#define D_3 (dist_tab[2])
#define D_MIN (CHAMP_MAX_SIZE * 2 + 1)
#define D_MAX (D_MIN * 2)

void		ft_do_sorted_tab(int *tab, int *tab_a, int *dist_tab, int size)
{
	int		i;
	int		swap;

	i = 0;
	tab[0] = tab_a[0];
	tab[1] = tab_a[1];
	tab[2] = tab_a[2];
	while (i < size - 1)
	{
		if ((tab[i]) <= (tab[i + 1]))
			i++;
		else
		{
			swap = (tab[i]);
			(tab[i]) = (tab[i + 1]);
			(tab[i + 1]) = swap;
			i = 0;
		}
	}
	dist_tab[0] = tab[1] - tab[0];
	dist_tab[1] = tab[2] - tab[1];
	dist_tab[2] = MEM_SIZE - tab[2] + tab[0];
}

/*
**	IF there is only one already given address
**		--> the other 3 are equally distant at : MEM_SIZE / 4 from each other.
*/

void		ft_j_one(int *address, int x, t_vm *vm)
{
	address[1] = ((address[0] + (MEM_SIZE / 4)) % MEM_SIZE);
	address[2] = ((address[1] + (MEM_SIZE / 4)) % MEM_SIZE);
	address[3] = ((address[2] + (MEM_SIZE / 4)) % MEM_SIZE);
	ft_fill_vma(vm, address, x, 1);
}

/*
**	IF there are already 2 given addresses...
**	The minimum required space to put a player between two adress is
**		D_MIN == CHAMP_MAX_SIZE * 2 + 1 == 1365 (also MEM_SIZE / 3)
**
**	IF there is enough space to put one champ, but less than the 2/3
**	of MEM_SIZE, we'll put only one player at MID, the other one above the MAX.
**		Ex:  <-P1(MIN)-----(MID)-----P2(MAX)----->
**			<-P1(MIN)-----P3(MID)-----P2(MAX)---P4-->
**
**	ELSE, we do a ternary:
**		IF MID > 2/3 * MEM_SIZE, we simply divide MID by 3 to put the
**			last 2 players between the 2 firsts, at equal distances;
**		Ex:  <-P1---------------P2->
**			<-P1-----P3-----P4-----P2->
**
**		ELSE we do the same between P2->P1, which will be bigger
**			than 2/3 * MEM_SIZE.
**		Ex:  <-------P1--P2------->
**			<--P4-----P1--P2-----P3--->
*/

void		ft_j_two(int *address, int x, t_vm *vm)
{
	if (MID_3 <= D_MAX && MID_3 >= D_MIN)
	{
		address[2] = (MIN_3 + (MID_3 / 2));
		address[3] = (MAX_3 + ((MEM_SIZE - MAX_3 + MIN_3) / 2));
	}
	else
	{
		address[2] = (MID_3 > (MEM_SIZE / 2)) ? (MIN_3 + (MID_3 / 3)) : MAD_4;
		address[3] = (MID_3 > (MEM_SIZE / 2)) ? \
					(address[2] + (MID_3 / 3)) : MAD_5;
	}
	ft_fill_vma(vm, address, x, 2);
}

/*
**	IF there are already 3 given addresses
**		--> We determine the area with the more space
**	First we sort the int array of given address in ft_do_sorted_tab;
**	Then we call D1 the distance between the 1st adress and the second,
**	D2 the distance between the 2nd and the 3rd and the 1st;
**	Finally, we just put the last player at the middle of the biggest area.
*/

void		ft_j_three(int *address, int *sort_add, int *dist_tab, t_vm *vm)
{
	if (D_1 > D_2)
		address[3] = (D_1 > D_3) ? \
		(sort_add[0] + (D_1 / 2)) : ((sort_add[2] + (D_3 / 2)) % MEM_SIZE);
	else
		address[3] = (D_2 >= D_3) ? \
		(sort_add[1] + (D_2 / 2)) : ((sort_add[2] + (D_3 / 2)) % MEM_SIZE);
	ft_fill_vma(vm, address, vm->nbr_players, 3);
}

/*
**	If there are four players:
**	We create an int array of [x] addresses.
**	In the first loop, we fill it with the already given addresses.
**	Then we deal with a function for every possible case.
*/

void		ft_four(t_vm *vm, int j, int x, int i)
{
	int		address[x];
	int		sort_add[x];
	int		dist_tab[x];
	int		nb;

	nb = 0;
	while (nb != x)
	{
		if (vm->a[nb] != -1)
		{
			address[i] = vm->a[nb];
			i++;
		}
		nb++;
	}
	if (j == 1)
		ft_j_one(address, x, vm);
	else if (j == 2)
		ft_j_two(address, x, vm);
	else if (j == 3)
	{
		ft_do_sorted_tab(sort_add, address, dist_tab, x);
		ft_j_three(address, sort_add, dist_tab, vm);
	}
}
