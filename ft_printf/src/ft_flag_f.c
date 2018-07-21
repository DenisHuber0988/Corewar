/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:27:33 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 20:09:13 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static void			ft_check_data(t_data *data, double nb, size_t size)
{
	if (data->precision_field && !data->precision)
	{
		data->zero = 0;
		data->precision = 6;
	}
	if (!data->precision_field)
		data->precision = 6;
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

static char			ft_check_sign(t_data *data, long double nb, char *signe)
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

static long double	ft_length(char **format, t_data *data, va_list *arg)
{
	if (data->length == L || **format == 'F')
		return ((long double)va_arg(*arg, double));
	else
		return ((double)(va_arg(*arg, double)));
}

int					ft_flag_f(char **format, va_list *arg, t_data *data)
{
	double		nb;
	char		*nbr;
	char		signe;
	size_t		size;

	nb = ft_length(format, data, arg);
	nbr = ft_itoa_base(nb, 10);
	ft_buffer(nbr, data, ft_strlen(nbr));
	ft_buffer(".", data, 1);
	nb -= ft_atoll((const char*)nbr);
	if (nb < 0)
		nb = -nb;
	signe = ft_check_sign(data, nb, &signe);
	data->len = ft_strlen(nbr);
	size = data->len + 1 + ((signe) ? 1 : 0);
	ft_check_data(data, nb, size);
	nb *= ft_power(10, data->precision + 1, 1);
	ft_memset(nbr, 0, data->len);
	ft_memdel((void**)&nbr);
	nbr = ft_itoa_base(nb + 1, 10);
	signe = ft_check_sign(data, nb, &signe);
	ft_buffer(nbr, data, data->precision);
	ft_memdel((void**)&nbr);
	return (size + data->precision);
}
