/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_wstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:04:11 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 19:26:18 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int	ft_length(wchar_t *s, size_t size)
{
	while (*s)
	{
		if (*s <= 0x7F)
			size += 1;
		else if (*s <= 0x7FF)
			size += 2;
		else if (*s <= 0xFFFF)
			size += 3;
		else if (*s <= 0x10FFFF)
			size += 4;
		else
			size += 0;
		s++;
	}
	return (size);
}

static int	ft_handle_minus(wchar_t *s, t_data *data, size_t size)
{
	if (data->precision_field)
	{
		while (data->precision >= ft_wlen(*s))
		{
			data->precision -= ft_wlen(*s);
			ft_handle_wchar(*s, data, size);
		}
		if (data->width)
			ft_printf_flag(' ', data, data->width - MIN(size, ft_wlen(*s)));
	}
	else
	{
		while (*s)
			ft_handle_wchar(*s++, data, size);
		if (data->width)
			ft_printf_flag(' ', data, data->width - size);
	}
	size = MAX(size, data->width);
	return (size);
}

static int	ft_handle_width(wchar_t *s, t_data *data, size_t size)
{
	if (data->width > size)
	{
		ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
		data->width_field = 0;
	}
	if (!data->precision)
		while (*s)
			size += ft_handle_wchar(*s++, data, size);
	else
	{
		while (data->precision >= ft_wlen(*s))
		{
			data->precision -= ft_wlen(*s);
			size += ft_handle_wchar(*s, data, size);
		}
	}
	return (MIN(size, data->width));
}

static int	ft_handle_precis(wchar_t *s, t_data *data, size_t size)
{
	if (!data->width_field)
	{
		while (data->precision >= ft_wlen(*s))
		{
			data->precision -= ft_wlen(*s);
			size += ft_handle_wchar(*s++, data, size);
		}
	}
	else
	{
		if (data->width > data->precision)
		{
			ft_printf_flag((data->zero) ? '0' : ' ', data,
					data->width - MIN(ft_wlen(*s), data->precision));
			data->width_field = 0;
		}
		while (data->precision >= ft_wlen(*s))
		{
			data->precision -= ft_wlen(*s);
			size += ft_handle_wchar(*s++, data, size);
		}
		size = MIN(data->precision, size);
	}
	return (MAX(size, data->width));
}

int			ft_handle_wstr(wchar_t *s, t_data *data, va_list *arg, size_t size)
{
	s = (wchar_t*)va_arg(*arg, char*);
	if (!s)
		s = L"(null)";
	if (data->precision_field || data->width_field)
	{
		size = ft_length(s, size);
		if (data->precision >= data->width)
			data->width_field = 0;
		if (data->precision >= size)
			data->precision_field = 0;
	}
	if (data->minus)
		size = ft_handle_minus(s, data, size);
	else if (data->precision_field)
		size = ft_handle_precis(s, data, 0);
	else if (data->width_field)
		size = ft_handle_width(s, data, size);
	else
	{
		size = 0;
		while (*s)
			size += ft_handle_wchar(*s++, data, 0);
	}
	return (size);
}
