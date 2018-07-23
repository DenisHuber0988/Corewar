/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:03:27 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:19:29 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int	ft_handle_minus(char **nbr, t_data *data, size_t size, char *signe)
{
	if (data->sharp && **nbr != '0')
		ft_printf_flag('0', data, 1);
	if (!data->width_field)
	{
		if (data->plus)
			ft_printf_flag(*signe, data, 1);
		ft_buffer(*nbr, data, data->len);
	}
	else
	{
		if (data->plus)
			ft_printf_flag(*signe, data, 1);
		if (data->precision_field)
		{
			ft_printf_flag('0', data, data->precision - size + data->plus);
			size = data->width - data->precision;
		}
		ft_buffer(*nbr, data, data->len);
		if (data->precision_field)
			ft_printf_flag(' ', data, size - data->plus);
		else
			ft_printf_flag(' ', data, data->width - data->len -
					(data->plus || data->sharp));
	}
	return (MAX(data->width, size));
}

static int	ft_handle_signe(t_data *data, size_t size, char *signe)
{
	ft_printf_flag(*signe, data, 1);
	if (data->precision_field)
		ft_printf_flag('0', data, data->precision - data->len);
	return (MAX(size, data->precision));
}

static int	ft_handle_width(char **nbr, t_data *data, size_t size, char *signe)
{
	if (data->zero)
	{
		if (data->plus)
			ft_printf_flag(*signe, data, 1);
		if (data->space)
			ft_printf_flag(' ', data, 1);
		ft_printf_flag('0', data, data->width - size - data->space);
	}
	else
	{
		ft_printf_flag(' ', data, data->width - size - data->sharp);
		if (data->sharp && **nbr != '0')
			ft_printf_flag('0', data, 1);
		if (data->plus)
			ft_printf_flag('+', data, 1);
	}
	return (MAX(size, data->width));
}

static int	ft_handle_precis(t_data *data, size_t size, char *signe)
{
	if (!data->width_field)
	{
		if (data->plus)
			ft_handle_signe(data, size, signe);
		else
			ft_printf_flag('0', data,
					data->precision - data->len - data->sharp);
		size = MAX(size, data->precision);
	}
	else
	{
		ft_printf_flag(' ', data, data->width - data->precision - data->plus);
		if (data->plus)
			ft_handle_signe(data, size, signe);
		else
			ft_printf_flag('0', data, data->precision - data->len);
		size = MAX(size, data->width);
	}
	return (size);
}

int			ft_handle_pos(char **nbr, t_data *data, size_t size, char *signe)
{
	if (data->sharp && (data->width_field || data->precision_field))
		size--;
	if (data->minus && data->width_field)
		size = ft_handle_minus(nbr, data, size, signe);
	else if (data->precision_field)
		size = ft_handle_precis(data, size, signe);
	else if (data->width_field)
		size = ft_handle_width(nbr, data, size, signe);
	else if (!data->plus && data->space)
	{
		ft_printf_flag(' ', data, 1);
		size++;
	}
	else if (!data->precision_field && !data->width_field)
		ft_printf_flag(*signe, data, 1);
	if (!data->minus)
		ft_buffer(*nbr, data, data->len);
	ft_memdel((void**)nbr);
	return (size);
}
