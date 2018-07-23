/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:54:05 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:16:57 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static void				ft_check_data(t_data *data, unsigned long long nb,
		size_t size)
{
	if (data->width_field || data->precision_field)
	{
		if (data->width <= size || data->precision >= data->width)
			data->width_field = 0;
		if (data->precision <= data->len && nb != 0)
			data->precision_field = 0;
	}
	if (!data->width_field)
		data->minus = 0;
	data->plus = 0;
	data->space = 0;
}

static uintmax_t		ft_length(char **format, t_data *data, va_list *arg)
{
	if (data->length == hh && **format != 'O')
		return ((unsigned long long)
				((unsigned char)va_arg(*arg, unsigned int)));
	else if (data->length == h && **format != 'O')
		return ((unsigned long long)
				((unsigned short int)va_arg(*arg, unsigned int)));
	else if (data->length == l || **format == 'O')
		return ((unsigned long long)va_arg(*arg, unsigned long));
	else if (data->length == ll)
		return ((unsigned long long)va_arg(*arg, unsigned long long));
	else if (data->length == j)
		return ((uintmax_t)va_arg(*arg, uintmax_t));
	else if (data->length == z)
		return ((unsigned long long)va_arg(*arg, size_t));
	else if (data->length == t)
		return ((ptrdiff_t)va_arg(*arg, ptrdiff_t));
	else
		return ((unsigned long long)(va_arg(*arg, unsigned int)));
}

int						ft_flag_o(char **format, va_list *arg, t_data *data)
{
	unsigned long long		nb;
	size_t					size;
	char					*nbr;

	nb = ft_length(format, data, arg);
	nbr = ft_utoa_base(nb, 8);
	data->len = ft_strlen((const char*)nbr);
	size = data->len + ((data->sharp && nb != 0) ? 1 : 0);
	ft_check_data(data, nb, size);
	if (data->sharp && !data->width_field && nb != 0)
		ft_buffer("0", data, 1);
	if (nb == 0 && data->precision_field && !data->precision)
	{
		if (data->sharp && !data->width_field)
			ft_buffer("0", data, 1);
		ft_memdel((void**)&nbr);
		return (ft_handle_zero(data));
	}
	return (ft_handle_pos(&nbr, data, size, "\0"));
}
