/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 16:18:29 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/04 15:02:10 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Take the value for a register and check REG_NUMBER wasn't changed
**	to avoid any segfault.
*/

void		recup_reg(t_vm *vm, t_player *player, int index)
{
	int		param;
	int		adr;

	if (REG_NUMBER < 1 || REG_NUMBER < 16)
	{
		if (REG_NUMBER < 1)
			ft_printf("REG_NUMBER was changed in .h and is inferior to 1!\n");
		else
			ft_printf("REG_NUMBER was changed in .h and is inferior to 16!\n");
		exit(1);
	}
	player->arg[index] = 0;
	adr = (player->address + player->tmpc + 1) % MEM_SIZE;
	if (adr < 0)
		adr += MEM_SIZE;
	param = vm->arena[adr];
	if (param < 1 || param > REG_NUMBER)
	{
		player->arg[index] = -1;
		return ;
	}
	player->arg[index] = param;
	player->tmpc += 1;
}

/*
**	Take the value for a Direct on 4 octets.
*/

void		recup_dir4(t_vm *vm, t_player *player, int index)
{
	int		tmp;
	int		param[4];
	int		adr;

	tmp = 0;
	ft_bzero(param, sizeof(param));
	player->arg[index] = 0;
	adr = player->address + player->tmpc;
	if (adr < 0)
		adr += MEM_SIZE;
	while (tmp < 4)
	{
		param[tmp] = vm->arena[(adr + tmp + 1) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 4)
	{
		player->arg[index] += param[tmp++];
		if (tmp < 4)
			player->arg[index] <<= 8;
	}
	player->tmpc += 4;
}

/*
**	Take the value for a Direct on 2 octets or an Index.
*/

void		recup_dir_index(t_vm *vm, t_player *player, int index)
{
	int		tmp;
	int		param[2];
	int		adr;

	player->arg[index] = 0;
	tmp = 0;
	ft_bzero(param, sizeof(param));
	adr = player->address + player->tmpc;
	if (adr < 0)
		adr += MEM_SIZE;
	while (tmp < 2)
	{
		param[tmp] = vm->arena[(adr + tmp + 1) % MEM_SIZE];
		tmp++;
	}
	tmp = 0;
	while (tmp < 2)
	{
		player->arg[index] += param[tmp++];
		if (tmp < 2)
			player->arg[index] <<= 8;
	}
	player->tmpc += 2;
}
