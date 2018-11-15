/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 16:11:35 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/05 14:23:34 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static void		call_live(t_vm *vm, t_player *player, int *arg, int ret)
{
	t_player	*tmp;

	tmp = &vm->player[ret];
	if (tmp != player)
		tmp->lives_p += 1;
	(player->number == arg[0]) ? player->lives_p++ : 0;
	vm->last_live = tmp->number;
	vm->last_color = tmp->color;
	ft_memset(vm->winner_name, 0, PROG_NAME_LENGTH + 1);
	ft_memmove((void*)&(vm->winner_name), &(tmp->name), PROG_NAME_LENGTH);
	if (vm->t == 2)
		ft_printf("Player %s n° %d is alive at cycle [%d]!\n",
		tmp->name, tmp->number, vm->cycle);
}

int				recup(t_vm *vm, t_player *player, int index, int adr)
{
	int		tmp;
	int		param[4];

	tmp = 0;
	ft_bzero(param, sizeof(param));
	player->arg[index] = 0;
	while (tmp < 4)
	{
		param[tmp] = vm->arena[(adr + tmp) % MEM_SIZE];
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
	return (player->arg[index]);
}

int				ft_check_reg(int reg, t_vm *vm, int nbr_pl)
{
	int	i;

	i = 0;
	while (i < nbr_pl)
	{
		if (vm->player[i].number == reg)
			return (i);
		i++;
	}
	return (-1);
}

int				op_live(t_vm *vm, t_player *player, int *arg)
{
	int			ret;
	int			adr;

	adr = player->address + player->pc + 1;
	arg[0] = recup(vm, player, 0, adr);
	move_pc(vm, player);
	ret = ft_check_reg(arg[0], vm, vm->nbr_players);
	player->lives = 1;
	vm->nbr_live += 1;
	if (ret != -1)
	{
		call_live(vm, player, arg, ret);
		return (OP_SUCCESS);
	}
	else if (vm->t == 2)
	{
		ft_printf("Unknown Player says 'Hi. The Cake is a lie. I'm ALIVE'");
		ft_printf(" at cycle [%d]\n", vm->cycle);
	}
	return (OP_ERROR);
}
