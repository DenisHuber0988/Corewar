/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 17:54:34 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 19:26:02 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int		ft_handle_minus(char *s, t_data *data, size_t size)
{
	if (data->precision_field)
	{
		ft_buffer(s, data, data->precision);
		if (data->width)
			ft_printf_flag(' ', data, data->width - data->precision);
		size = (data->width) ? MAX(size, data->width) : data->precision;
	}
	else
	{
		ft_buffer(s, data, size);
		if (data->width)
			ft_printf_flag(' ', data, data->width - size);
		size = (data->width) ? MAX(size, data->width) : size;
	}
	return (size);
}

static int		ft_handle_width(char *s, t_data *data, size_t size)
{
	if (!data->precision_field)
	{
		if (data->width > size)
			ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
		ft_buffer(s, data, size);
	}
	else
	{
		size = (data->precision <= size) ? data->precision : size;
		if (data->width > size)
			ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
		ft_buffer(s, data, size);
	}
	size = MAX(size, data->width);
	return (size);
}

static int		ft_handle_precis(char *s, t_data *data, size_t size)
{
	if (!data->width_field)
	{
		size = (data->precision <= size) ? data->precision : size;
		ft_buffer(s, data, size);
	}
	else
	{
		size = (data->precision <= size) ? data->precision : size;
		ft_printf_flag((data->zero) ? '0' : ' ', data,
				data->width - data->precision);
		ft_buffer(s, data, size);
	}
	return (size);
}

int				ft_handle_str(char *s, t_data *data, size_t size)
{
	if (!s)
		s = "(null)";
	if (data->minus)
		size = ft_handle_minus(s, data, size);
	else if (data->width_field)
		size = ft_handle_width(s, data, size);
	else if (data->precision_field)
		size = ft_handle_precis(s, data, size);
	else
		ft_buffer(s, data, data->len);
	return (size);
}
