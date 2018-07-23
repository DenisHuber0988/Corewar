/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:40:34 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/25 17:28:26 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static void		ft_initiate_data(t_data *data)
{
	data->minus = 0;
	data->plus = 0;
	data->sharp = 0;
	data->space = 0;
	data->zero = 0;
	data->width_field = 0;
	data->precision_field = 0;
	data->width = 0;
	data->precision = 0;
	data->length = 0;
	data->len = 0;
}

static int		ft_printf_build(char **format, va_list *arg,
		t_data *data, size_t ret)
{
	(*format)++;
	if (**format == '\0')
		return (-1);
	while (!ft_strchr("bcCdDfFinoOpuUsSxX%", **format))
	{
		if (ft_flag(format, data) == NULL)
			return (-1);
		if (ft_width(format, arg, data) == NULL)
			return (-1);
		if (ft_precision(format, arg, data) == NULL)
			return (-1);
		if (ft_size(format, data) == NULL)
			return (-1);
		if (ft_error(format) == NULL)
			return (ft_printf_conversion(format, arg, data, ret));
		if (**format == '\0')
			return (-1);
	}
	if (!ft_strchr("bcCdDfFinoOpuUsSxX%", **format))
		return (-1);
	else
		ret = ft_printf_conversion(format, arg, data, ret);
	ft_initiate_data(data);
	return (ret);
}

void			ft_buffer(const char *cpy, t_data *data, size_t size)
{
	size_t	tmp;
	size_t	index;

	tmp = 0;
	index = 0;
	if (!(cpy || size))
		return ;
	while (BUFF - data->i < size)
	{
		tmp = BUFF - data->i;
		ft_memcpy((void*)&data->buf[data->i], (const void*)&cpy[index], tmp);
		size -= tmp;
		data->i += tmp;
		index += tmp;
		write(1, (const void*)data->buf, data->i);
		ft_memset((void*)data->buf, 0, BUFF);
		data->i = 0;
	}
	ft_memcpy((void*)&data->buf[data->i], (const void*)&cpy[index], size);
	data->i += size;
}

static int		ft_check_printf(const char *format, t_data *data,
		va_list *arg, int ret)
{
	size_t	size;

	size = 0;
	while (*format)
	{
		if (*format == '%')
		{
			ret = ft_printf_build((char**)&format, arg, data, size);
			if (ret == -1 || *format == '\0')
				break ;
			size += ret;
		}
		else if (*format != '\0')
		{
			ft_buffer(format, data, 1);
			size++;
		}
		format++;
	}
	return (size);
}

int				ft_printf(const char *format, ...)
{
	int		size;
	va_list	arg;
	t_data	data;

	ft_bzero(&data, sizeof(data));
	va_start(arg, format);
	size = ft_check_printf(format, &data, &arg, 0);
	va_end(arg);
	write(1, (const void*)data.buf, data.i);
	return (size);
}
