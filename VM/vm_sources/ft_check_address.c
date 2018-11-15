/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:01:14 by mkamel            #+#    #+#             */
/*   Updated: 2018/09/25 20:23:11 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#define MAX_3 ((address[0] > address[1]) ? address[0] : address[1])
#define MIN_3 ((address[0] < address[1]) ? address[0] : address[1])
#define MID_3 (MAX_3 - MIN_3)
#define MAD_3 ((MAX_3 + ((MEM_SIZE - MAX_3 + MIN_3) / 2)) % MEM_SIZE)

void		ft_fill_vma(t_vm *vm, int *address, int x, int j)
{
	int		i;

	i = 0;
	while (i < x)
	{
		vm->a[i] == -1 ? vm->a[i] = address[j++] : 0;
		i++;
	}
}

/*
**	If there are three players:
**	We create an int array of [x] addresses.
**	In the first loopm, we fill it with the already given addresses.
**
**	Then:
**	IF there is only one already given address
**		--> the other two are equally distant at : MEM_SIZE / 3 from each other.
**	ELSE IF there are already 2 given addresses
**		--> We determine the area with the more space
**		ex : Case 1 (<--P1---"MID/2"---P2-->)
**		 and Case 2 (<----P1-"MID/2"-P2---->)
**	MID is the distance between the 2 given addresses (== P2 - P1).
**	IF MID >= MEM_SIZE / 2,
**		Then it is the biggest area and we put the last adress at its centre,
**		like in the Case 1 above.
**	ELSE, like in Case 2 above,
**		we determine the distance P2->P1 : MEM_SIZE - MAX_3 + MIN_3. Then we
**		divide it by 2, to be at the center of it.
**		Finally we apply a % MEM_SIZE in order not to be above MEM_SIZE.
**
**	Finally
**	ft_fill_vma gives the addresses of our array to the corresponding players.
*/

void		ft_three(t_vm *vm, int j, int x, int i)
{
	int		address[x];
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
	{
		address[1] = ((address[0] + (MEM_SIZE / 3)) % MEM_SIZE);
		address[2] = ((address[1] + (MEM_SIZE / 3)) % MEM_SIZE);
		ft_fill_vma(vm, address, x, 1);
	}
	else if (j == 2)
	{
		address[2] = (MID_3 >= (MEM_SIZE / 2)) ? (MAX_3 - (MID_3 / 2)) : MAD_3;
		ft_fill_vma(vm, address, x, 2);
	}
}

/*
**	ft_check_ad will deal the adressess in case of several players being called,
**	and the presence if the flag -a in at least 1 but not every cases.
**	The int 'x' is the total number of called players.
**	the int 'j' is the number of players with a flag -a.
**
**	If there are only two players :
**		the int 'i' will be the number of the player without an address in the
**		vm->a array;
**		the int 'ad' will give it the corresponding address, at MEM_SIZE / 2
**		from the other player.
*/

void		ft_check_ad(t_vm *vm, int x, int j)
{
	int		ad;
	int		i;

	ad = 0;
	if (x == 2 && j != 2)
	{
		i = (vm->a[0] == -1) ? 1 : 0;
		ad = ((vm->a[i] + (MEM_SIZE / 2)) % MEM_SIZE);
		i = (vm->a[0] == -1) ? 0 : 1;
		vm->a[i] = ad;
	}
	else if (x == 3 && j != 3)
		ft_three(vm, j, x, 0);
	else if (x == 4 && j != 4)
		ft_four(vm, j, x, 0);
}
