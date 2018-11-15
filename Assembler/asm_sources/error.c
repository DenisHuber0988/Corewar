/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:23:36 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:04:34 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"
#include "errno.h"

/*
**	message error
*/

void	error(int n)
{
	if (n < 0)
		ft_putendl("ERROR");
	if (n == -1)
		ft_putendl("Wrong argument number or an instruction");
	if (n == -2)
		ft_putendl(strerror(errno));
	if (n == -3)
		ft_putendl("Invalid extension");
	if (n == -4)
		ft_putendl("Invalid name or comment");
	if (n == -5)
		ft_putendl("Failed to malloc");
	if (n == -6)
		ft_putendl("Invalid label");
	if (n == -7)
		ft_putendl("Same label appears twice or more");
	if (n == -8)
		ft_putendl("Invalid instruction");
	if (n == -9)
		ft_putendl("Wrong number of registry");
	error1(n);
	exit(1);
}

/*
**	message error bis
*/

void	error1(int n)
{
	if (n == -10)
		ft_putendl("Indirect argument too long");
	if (n == -11)
		ft_putendl("Invalid direct argument");
	if (n == -12)
		ft_putendl("Invalid type of argument for an instruction");
	if (n == -13)
		ft_putendl("Call to unknown label");
	if (n == -14)
		ft_putendl("No instruction");
	if (n == -15)
		ft_putendl("Program too big");
	if (n == -16)
		ft_putendl("Argument missing");
}
