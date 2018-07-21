/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:20:35 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:18:18 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int	ft_handle_minus(char **nbr, t_data *data, size_t size)
{
	ft_buffer("0x", data, 2);
	if (!data->width_field)
		ft_buffer(*nbr, data, data->len);
	else
	{
		if (data->precision_field)
		{
			ft_printf_flag('0', data, data->precision - size);
			size = data->width - data->precision;
		}
		ft_buffer(*nbr, data, data->len);
		if (data->precision_field)
			ft_printf_flag(' ', data, size);
		else
			ft_printf_flag(' ', data, ((**nbr == '0') ?
						data->width - size - 1 : data->width - size));
	}
	return (MAX(data->width, size));
}

static int	ft_handle_width(char **nbr, t_data *data, size_t size)
{
	if (data->zero)
		ft_buffer("0x", data, 2);
	ft_printf_flag((data->zero) ? '0' : ' ', data, ((**nbr == '0') ?
				data->width - size - 1 : data->width - size));
	if (!data->zero)
		ft_buffer("0x", data, 2);
	ft_buffer(*nbr, data, data->len);
	return (MAX(size, data->width));
}

static int	ft_handle_precis(t_data *data, size_t size)
{
	ft_buffer("0x", data, 2);
	if (!data->width_field)
	{
		ft_printf_flag('0', data, data->precision - data->len);
		size = (data->precision) ? MAX(data->len, data->precision) + 2 : size;
	}
	else
	{
		ft_printf_flag(' ', data, data->width - data->precision);
		ft_printf_flag('0', data, data->precision - data->len);
	}
	return (size);
}

int			ft_handle_ptr(char **nbr, t_data *data, size_t size)
{
	if (!data->minus && !data->precision && !data->width_field && **nbr == '0')
	{
		ft_buffer("0x", data, 2);
		if (!data->precision_field && !data->width_field)
		{
			ft_buffer(*nbr, data, data->len);
			size++;
		}
	}
	else if (data->minus)
		size = ft_handle_minus(nbr, data, size);
	else if (data->precision_field && data->precision)
		size = ft_handle_precis(data, size);
	else if (data->width_field)
		size = ft_handle_width(nbr, data, size);
	else if (!data->precision_field && !data->width_field && **nbr != '0')
	{
		ft_buffer("0x", data, 2);
		ft_buffer(*nbr, data, data->len);
	}
	if (!data->minus && data->precision_field && data->precision)
		ft_buffer(*nbr, data, data->len);
	ft_memdel((void**)nbr);
	return (size);
}
