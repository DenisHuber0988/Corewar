/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:57:44 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/21 15:34:43 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/virtual_machine.h"

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
				ft_error(vm, "Invalid file -> ", av, 1);
		}
		else
			ft_error(vm, "Invalid file -> ", av, 1);
	}
	else
		ft_error(vm, "Incorrect extension -> ", av, 1);
}

void			unknown_instruction(t_vm *vm, char *av, char *next)
{
	if (my_isdigit(av) || ft_strstr(av, "."))
	{
		if (!my_isdigit(next))
			return ;
		else
			ft_error(vm, "Unknown instruction -> ", next, 1);
	}
	if (ft_strcmp(av, "-n") && ft_strcmp(av, "-a") &&
			ft_strcmp(av, "-dump") && ft_strcmp(av, "-v"))
		ft_error(vm, "Unknown instruction -> ", av, 1);
}

void			ft_error(t_vm *vm, char *msg, char *type, int n)
{
	if (n)
		ft_putstr_fd("Error : ", 2);
	else
		ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(type, 2);
	ft_free(vm);
	exit(1);
}
