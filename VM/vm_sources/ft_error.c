/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:57:44 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/23 16:46:35 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static void		ft_free(t_vm *vm)
{
	(void)vm;
}

void			valid_extension(t_vm *vm, char *av)
{
	int	fd;

	if (ft_strstr(av, ".cor"))
	{
		fd = open(av, O_RDONLY);
		if (fd >= 0)
		{
			if (read(fd, (void*)av, 0) != -1)
				vm->nbr_players++;
			else
			{
				if (close(fd) == -1)
					vm_error(vm, "Couldn't close the file.", "", 1);
				vm_error(vm, "Can't read the file -> ", av, 1);
			}
		}
		else
		{
			if (close(fd) == -1)
				vm_error(vm, "Couldn't close the file.", "", 1);
			vm_error(vm, "Invalid file -> ", av, 1);
		}
	}
	else
		vm_error(vm, "Incorrect extension -> ", av, 1);
}

void			unknown_instruction(t_vm *vm, char *av, char *next)
{
	if (vm_isdigit(av) || ft_strstr(av, "."))
	{
		if (!vm_isdigit(next))
			return ;
		else
			vm_error(vm, "Unknown instruction -> ", next, 1);
	}
	if (ft_strcmp(av, "-n") && ft_strcmp(av, "-a") &&
			ft_strcmp(av, "-dump") && ft_strcmp(av, "-v"))
		vm_error(vm, "Unknown instruction -> ", av, 1);
}

void			vm_error(t_vm *vm, char *msg, char *type, int n)
{
	if (n)
		ft_putstr("Error : ");
	else
		ft_putstr("Usage : ");
	ft_putstr_fd(msg, 2);
	if (*type)
		ft_printf("[%s]\n", type);
	else
		ft_putchar('\n');
	ft_free(vm);
	exit(1);
}
