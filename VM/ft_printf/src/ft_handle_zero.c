/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:54:51 by dhuber            #+#    #+#             */
/*   Updated: 2018/02/27 17:58:54 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

int			ft_handle_zero(t_data *data)
{
	if (data->sharp)
		return (1);
	else if (data->width_field)
	{
		ft_printf_flag(' ', data, data->width - data->plus);
		if (data->plus)
			ft_printf_flag('+', data, 1);
		return (data->width);
	}
	else if (!data->width_field && data->plus)
	{
		ft_printf_flag('+', data, 1);
		return (1);
	}
	else if (data->space)
	{
		ft_printf_flag(' ', data, 1);
		return (1);
	}
	else
		return (0);
}
