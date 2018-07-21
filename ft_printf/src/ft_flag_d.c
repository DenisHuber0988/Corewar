/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:27:16 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:15:26 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static void			ft_check_data(t_data *data, long long nb, size_t size)
{
	if (data->precision_field)
		data->zero = 0;
	if (data->width_field || data->precision_field)
	{
		if (data->width <= size || data->precision >= data->width)
			data->width_field = 0;
		if (data->precision <= data->len && nb != 0)
			data->precision_field = 0;
	}
	if (!data->width_field)
		data->minus = 0;
	data->sharp = 0;
}

static char			ft_check_sign(t_data *data, long long nb, char *signe)
{
	if (nb < 0 || data->plus || data->zero)
	{
		if (nb == -nb && nb != 0)
			*signe = '\0';
		else if (nb < 0)
			*signe = '-';
		else if (nb >= 0 && data->plus)
			*signe = '+';
		else
			*signe = '\0';
	}
	else
		*signe = '\0';
	return (*signe);
}

static long long	ft_length(char **format, t_data *data, va_list *arg)
{
	if (data->length == hh && **format != 'D')
		return ((long long)((signed char)va_arg(*arg, int)));
	else if (data->length == h && **format != 'D')
		return ((long long)((short int)va_arg(*arg, int)));
	else if (data->length == l || **format == 'D')
		return ((long long)va_arg(*arg, long));
	else if (data->length == ll)
		return ((long long)va_arg(*arg, long long));
	else if (data->length == j)
		return ((long long)va_arg(*arg, intmax_t));
	else if (data->length == z)
		return ((long long)va_arg(*arg, size_t));
	else if (data->length == t)
		return ((ptrdiff_t)va_arg(*arg, ptrdiff_t));
	else
		return ((long long)(va_arg(*arg, int)));
}

int					ft_flag_d(char **format, va_list *arg, t_data *data)
{
	long long			nb;
	size_t				size;
	char				signe;
	char				*nbr;

	nb = ft_length(format, data, arg);
	nbr = ft_itoa_base((nb >= 0) ? nb : -nb, 10);
	data->len = ft_strlen((const char*)nbr);
	signe = ft_check_sign(data, nb, &signe);
	size = data->len + ((signe) ? 1 : 0);
	ft_check_data(data, nb, size);
	if (nb == 0 && data->precision_field == 1 && data->precision == 0)
	{
		ft_memdel((void**)&nbr);
		return (ft_handle_zero(data));
	}
	else if (nb >= 0)
		return (ft_handle_pos(&nbr, data, size, &signe));
	else
		return (ft_handle_neg(&nbr, data, size, &signe));
}
