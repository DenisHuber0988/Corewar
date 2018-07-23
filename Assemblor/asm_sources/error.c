/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:23:36 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:39:58 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

void	error(int n)
{
	if (n < 0)
		ft_putendl("ERROR");
	if (n == -1)
		ft_putendl("wrong argument number or an instruction");
	if (n == -2)
		ft_putendl("no valid champ");
	if (n == -3)
		ft_putendl("no valid extended");
	if (n == -4)
		ft_putendl("no valid name or comment");
	if (n == -5)
		ft_putendl("fail malloc");
	error1(n);
	exit(-1);
}

void	error1(int n)
{
	if (n == -6)
		ft_putendl("no valid label");
	if (n == -7)
		ft_putendl("same label");
	if (n == -8)
		ft_putendl("unexist instruction");
	if (n == -9)
		ft_putendl("wrong number of register");
	if (n == -10)
		ft_putendl("to longer indirect argument");
	if (n == -11)
		ft_putendl("bad direct argument");
	if (n == -12)
		ft_putendl("wrong type of argument for an instruction");
	if (n == -13)
		ft_putendl("call to unexisting label");
	if (n == -14)
		ft_putendl("nothing instruction");
}
