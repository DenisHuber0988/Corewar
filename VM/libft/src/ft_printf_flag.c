/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:45:55 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/04 14:11:31 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printf_flag(char c, t_data *data, size_t size)
{
	if (!c)
		return ;
	while (size)
	{
		ft_buffer(&c, data, 1);
		size--;
	}
}
