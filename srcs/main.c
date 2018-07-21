/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:16:02 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/21 15:42:15 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/virtual_machine.h"
#include <stdio.h>
/*
static void	print_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
			ft_putstr_fd("\n", 1);
		if (!(i % 2))
			ft_putstr_fd(" ", 1);
		ft_putchar_fd(vm->arena[i++], 1);
	}
}
*/
static void	print_vm(t_vm *vm)
{
	int	i;

	i = 0;
	printf("nbr_player = [%d]\n", vm->nbr_players);
	printf("dump = [%d]\n\n", vm->dump);
	while (i < MAX_PLAYERS)
	{
		printf("player %d = [%d]\n", i + 1, vm->n[i]);
		printf("a = [%d]\n\n", vm->a[i]);
		i++;
	}
	printf("v = [%d]\n\n", vm->v);
}

int			main(int ac, char **av)
{
	t_vm	vm;

	if (ac == 1)
		return (-1);
	init(&vm, ac, av);
	parse_flag(&vm);
	print_vm(&vm);
	//print_arena(&vm);
	return (0);
}
