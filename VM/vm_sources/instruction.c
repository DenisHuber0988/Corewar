/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:35:48 by mkamel            #+#    #+#             */
/*   Updated: 2018/10/04 14:57:11 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
**	Check the type of arg (REG/DIR/IND) and taking it in the arena.
**	If the type isn't correct it put -1 as an error and the instruction
**	will not be execute.
*/

static void		take_arg(t_vm *vm, t_player *player, t_base *tab, int i)
{
	int	index;

	index = 0;
	tab->nb_arg = g_op_tab[player->op - 1].nb_arg;
	while (index < tab->nb_arg)
	{
		if (tab->type[index] == REG_CODE)
			recup_reg(vm, player, index);
		else if (tab->type[index] == DIR_CODE)
		{
			if (!i)
				recup_dir4(vm, player, index);
			else
				recup_dir_index(vm, player, index);
		}
		else if (tab->type[index] == IND_CODE)
			recup_dir_index(vm, player, index);
		else
			player->type[index] = -1;
		index++;
	}
}

/*
**	Cut the opc in four and move the tmpc.
*/

static void		ft_type(t_vm *vm, t_player *player, t_base *tab)
{
	int adr;

	adr = (player->address + player->pc + 1) % MEM_SIZE;
	ft_bzero(player->arg, 3);
	ft_bzero(player->type, 4);
	ft_bzero(tab->type, 4);
	ft_bzero(tab, sizeof(tab));
	tab->opc = vm->arena[adr];
	tab->type[0] = tab->opc >> 6;
	tab->type[1] = (tab->opc >> 4) & 0x3;
	tab->type[2] = (tab->opc >> 2) & 0x3;
	tab->type[3] = tab->opc & 0x3;
	player->type[0] = tab->type[0];
	player->type[1] = tab->type[1];
	player->type[2] = tab->type[2];
	player->type[3] = tab->type[3];
	player->tmpc += 1 % 0xffff;
}

/*
**	Check the value for the pc.
**	If it's an instruction, it gives all the info to the struct t_player
**	else it moves the pc and tmpc.
*/

void			take_instruction(t_vm *vm, t_player *player)
{
	unsigned char		opc;
	int					adr;

	if (!player)
		return ;
	adr = (player->address + player->pc) % MEM_SIZE;
	opc = vm->arena[adr];
	if (opc > 0x0 && opc <= 0x10)
	{
		player->op = opc;
		player->instruction = 1;
		player->countdown = g_op_tab[opc - 1].cycle;
		player->is_opc = g_op_tab[opc - 1].carry;
		player->dir = g_op_tab[opc - 1].direct_bit;
	}
	else
	{
		move_pc(vm, player);
		player->tmpc += 1 % 0xffff;
	}
}

/*
**	ft_type : if there is an opc, determines the type (DIR, IND, REG) of
**	each parameter and
*/

void			exec_instruction(t_vm *vm, t_player *player,
		int (*ft_op)(t_vm*, t_player*, int*))
{
	t_base	tab;

	if (!player)
		return ;
	ft_bzero(&tab, sizeof(tab));
	if (player->is_opc)
		ft_type(vm, player, &tab);
	take_arg(vm, player, &tab, player->dir);
	ft_op(vm, player, player->arg);
	player->tmpc = player->pc;
	player->instruction = 0;
	player->countdown = 0;
	player->op = 0;
	player->is_opc = 0;
	ft_bzero(player->arg, 3);
	ft_bzero(player->type, 4);
	ft_bzero(tab.type, 4);
}
