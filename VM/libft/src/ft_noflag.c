/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noflag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:12:27 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/04 14:11:25 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			ft_check_data(t_data *data)
{
	if (data->width_field)
	{
		if (data->width <= 1)
			data->width_field = 0;
	}
	data->sharp = 0;
	data->plus = 0;
	data->space = 0;
}

int					ft_noflag(char **format, va_list *arg, t_data *data)
{
	(void)arg;
	(void)format;
	ft_check_data(data);
	if (data->minus)
	{
		ft_buffer("%", data, 1);
		if (data->width >= 1)
			ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - 1);
	}
	else
	{
		if (data->width >= 1)
			ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - 1);
		ft_buffer("%", data, 1);
	}
	return ((data->width_field) ? MAX(1, data->width) : 1);
}
