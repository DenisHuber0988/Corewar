/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrong.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:51:17 by dhuber            #+#    #+#             */
/*   Updated: 2018/02/26 18:55:36 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int		ft_handle_minus(t_data *data, size_t size, char *c)
{
	ft_buffer(c, data, size);
	if (data->width_field)
		ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
	return (MAX(size, data->width));
}

static int		ft_handle_width(t_data *data, size_t size, char *c)
{
	ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
	ft_buffer(c, data, size);
	return (MAX(size, data->width));
}

int				ft_wrong(char **format, va_list *arg, t_data *data)
{
	size_t	size;
	char	*c;

	(void)arg;
	c = *format;
	if (c == '\0' || **format == '\0')
		return (0);
	size = 1;
	if (data->minus)
		size = ft_handle_minus(data, size, c);
	else if (data->width_field)
		size = ft_handle_width(data, size, c);
	else
		ft_buffer(c, data, size);
	return (size);
}
