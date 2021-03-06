/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <dhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:30:08 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/04 14:10:53 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_handle_minus(char **nbr, t_data *data, size_t size)
{
	if (data->sharp)
		ft_buffer("0b", data, 2);
	if (!data->width_field)
		ft_buffer(*nbr, data, data->len);
	else
	{
		if (data->precision_field)
		{
			ft_printf_flag('0', data, data->precision - size + data->sharp);
			size = data->width - data->precision;
		}
		ft_buffer(*nbr, data, data->len);
		if (data->precision_field)
			ft_printf_flag(' ', data, size - data->plus);
		else
			ft_printf_flag(' ', data, data->width - data->len -
					((data->sharp) ? 2 : 0));
	}
	return (MAX(size, data->width));
}

static int	ft_handle_width(t_data *data, size_t size)
{
	if (data->zero)
	{
		if (data->sharp)
			ft_buffer("0b", data, 2);
		ft_printf_flag('0', data, data->width - size);
	}
	else
	{
		ft_printf_flag(' ', data, data->width - size);
		if (data->sharp)
			ft_buffer("0b", data, 2);
	}
	size = MAX(size, data->width);
	return (size);
}

static int	ft_handle_precis(t_data *data, size_t size)
{
	if (!data->width_field)
	{
		ft_printf_flag('0', data, data->precision - data->len);
		size = (data->sharp) ? MAX(size, data->precision) :
			MAX(size, data->precision);
	}
	else
	{
		ft_printf_flag(' ', data, data->width - data->precision - data->plus);
		ft_printf_flag('0', data, data->precision - data->len);
		size = (data->sharp) ? MAX(size, data->width) :
			MAX(size, data->width);
	}
	return ((data->sharp) ? size + 2 : size);
}

int			ft_handle_bin(char **nbr, t_data *data, size_t size)
{
	if (data->minus && data->width_field)
		size = ft_handle_minus(nbr, data, size);
	else if (data->precision_field)
		size = ft_handle_precis(data, size);
	else if (data->width_field)
		size = ft_handle_width(data, size);
	else if (!data->plus && data->space)
	{
		ft_printf_flag(' ', data, 1);
		size++;
	}
	if (!data->minus)
		ft_buffer(*nbr, data, data->len);
	ft_memdel((void**)nbr);
	return (size);
}
