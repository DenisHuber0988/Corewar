/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:16:02 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/23 18:30:33 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

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
	while (i < vm->nbr_players)
	{
		ft_printf("player %d = [%d]\n", i + 1, vm->player[i].number);
		ft_printf("a = [%d]\n\n", vm->player[i].address);
		ft_printf("vm name = [%s]\n", vm->player[i].name);
		ft_printf("vm comment = [%s]\n", vm->player[i].comment);
		i++;
	}
}

int			main(int ac, char **av)
{
	t_vm		vm;

	if (ac == 1)
		return (-1);
	init(&vm, ac, av);
	parse_flag(&vm);
	parse_champ(&vm);
	print_vm(&vm);
//	print_arena(&vm);
	return (0);
}
