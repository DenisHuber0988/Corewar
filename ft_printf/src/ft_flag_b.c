/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:20:28 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:15:08 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/libft.h"

static void			ft_check_data(t_data *data, long long nb, size_t size)
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
	if (nb == 0)
		data->sharp = 0;
}

static intmax_t		ft_length(char **format, t_data *data, va_list *arg)
{
	if (data->length == hh && **format != 'B')
		return ((long long)((signed char)va_arg(*arg, int)));
	else if (data->length == h && **format != 'B')
		return ((long long)((short int)va_arg(*arg, int)));
	else if (data->length == l || **format == 'B')
		return ((long long)va_arg(*arg, long));
	else if (data->length == ll)
		return ((long long)va_arg(*arg, long long));
	else if (data->length == j)
		return ((intmax_t)va_arg(*arg, intmax_t));
	else if (data->length == z)
		return ((long long)va_arg(*arg, size_t));
	else if (data->length == t)
		return ((ptrdiff_t)va_arg(*arg, ptrdiff_t));
	else
		return ((long long)(va_arg(*arg, int)));
}

int					ft_flag_b(char **format, va_list *arg, t_data *data)
{
	long long		nb;
	int				size;
	char			*nbr;

	(void)format;
	nb = ft_length(format, data, arg);
	nbr = ft_utoa_base(nb, 2);
	data->len = ft_strlen(nbr);
	size = data->len + ((data->sharp && nb != 0) ? 2 : 0);
	ft_check_data(data, nb, size);
	if (data->sharp && !data->width_field)
		ft_buffer("0b", data, 2);
	if (nb == 0 && data->precision_field && !data->precision)
	{
		ft_memdel((void**)&nbr);
		return (ft_handle_zero(data));
	}
	else
		return (ft_handle_bin(&nbr, data, size));
}
