/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_neg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:26:44 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:17:58 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int	ft_handle_minus(char **nbr, t_data *data, size_t size, char *signe)
{
	if (!data->width_field)
	{
		ft_printf_flag(*signe, data, 1);
		ft_buffer(*nbr, data, data->len);
	}
	else
	{
		ft_printf_flag(*signe, data, 1);
		if (data->precision_field)
		{
			ft_printf_flag('0', data, data->precision - size + 1);
			size = data->width - data->precision;
		}
		ft_buffer(*nbr, data, data->len);
		ft_printf_flag(' ', data, size - 1);
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

static int	ft_handle_width(t_data *data, size_t size, char *signe)
{
	if (data->zero)
	{
		ft_printf_flag(*signe, data, 1);
		ft_printf_flag('0', data, data->width - size);
	}
	else
	{
		ft_printf_flag(' ', data, data->width - size);
		ft_printf_flag(*signe, data, 1);
	}
	return (MAX(size, data->width));
}

static int	ft_handle_precis(t_data *data, size_t size, char *signe)
{
	if (!data->width_field)
	{
		ft_handle_signe(data, size, signe);
		size = MAX(size, data->precision) + 1;
	}
	else
	{
		ft_printf_flag(' ', data, data->width - data->precision - 1);
		ft_handle_signe(data, size, signe);
		size = MAX(size, data->width);
	}
	return (size);
}

int			ft_handle_neg(char **nbr, t_data *data, size_t size, char *signe)
{
	if (data->minus && data->width_field)
		size = ft_handle_minus(nbr, data, size, signe);
	else if (data->precision_field)
		size = ft_handle_precis(data, size, signe);
	else if (data->width_field)
		size = ft_handle_width(data, size, signe);
	else if (!data->precision_field && !data->width_field)
		ft_printf_flag(*signe, data, 1);
	if (!data->minus)
		ft_buffer(*nbr, data, data->len);
	ft_memdel((void**)nbr);
	return (size);
}
