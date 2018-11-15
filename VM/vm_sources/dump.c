/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:29:29 by mkamel            #+#    #+#             */
/*   Updated: 2018/09/25 18:59:55 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

/*
** Displays the arena every N cycles (specified on the command line)
*/

void			dump_memory_s(t_vm *vm, int i)
{
	char	*line;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
			!i ? ft_printf("%s0x%.4x : ", DEFAULT, i) : \
					ft_printf("%s%#.4x : ", DEFAULT, i);
		print_color(vm, i);
		if (!((i + 1) % 64) && i)
			ft_printf("%.2x\n", vm->arena[i++]);
		else
			ft_printf("%.2x ", vm->arena[i++]);
	}
	ft_printf("%scycle = [%7.7d]\n\n", DEFAULT, vm->cycle);
	if (get_next_line(1, &line) > 0)
		ft_memdel((void**)&line);
	else
	{
		free_all(vm);
		exit(1);
	}
	ft_printf("%s", DEFAULT);
}

/*
** Displays the final state of the arena, after a winner has been declared.
*/

void			dump(t_vm *vm, int i)
{
	ft_printf(CLEAR2);
	declare_winner(vm);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
			!i ? ft_printf("0x%.4x : ", i) : ft_printf("%#.4x : ", i);
		if (!((i + 1) % 64) && i)
			ft_printf("%.2x\n", vm->arena[i++]);
		else
			ft_printf("%.2x ", vm->arena[i++]);
	}
	ft_printf("Dump at the end of the party.\n");
}

/*
** Displays the arena mid-game... at the cycle specified on the command line.
** If there is a winner, the above 'dump' function is called instead.
**
** The index i prints every memory value, until MEM_SIZE
** (all values in the arena are displayed in hexadecimal)
** The first 'if' prints the full hex index of the first value of the line.
** The second 'if' prints the '\n' at the end of every line.
** The third 'else' prints the value at that index, followed by a space.
*/

void			dump_memory(t_vm *vm, int i)
{
	ft_printf(CLEAR2);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
			!i ? ft_printf("0x%.4x : ", i) : ft_printf("%#.4x : ", i);
		if (!((i + 1) % 64) && i)
			ft_printf("%.2x\n", vm->arena[i++]);
		else
			ft_printf("%.2x ", vm->arena[i++]);
	}
	free_all(vm);
	ft_printf("Dump before the end of the party.\n");
	exit(1);
}
