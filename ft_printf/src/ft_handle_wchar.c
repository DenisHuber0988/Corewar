/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_wchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 16:22:32 by dhuber            #+#    #+#             */
/*   Updated: 2018/06/22 19:22:58 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int	ft_handle_minus(char *s, t_data *data, size_t size)
{
	ft_buffer(s, data, size);
	if (data->width_field && !*s++)
		ft_printf_flag(' ', data, data->width - size);
	data->width_field = 0;
	return (MAX(size, data->width));
}

static int	ft_handle_width(char *s, t_data *data, size_t size)
{
	ft_printf_flag((data->zero) ? '0' : ' ', data, data->width - size);
	ft_buffer(s, data, size);
	return (MAX(size, data->width));
}

void		ft_into_char(wchar_t c, char *s, size_t size)
{
	if (size == 1)
		s[0] = c;
	else if (size == 2)
	{
		s[0] = (c >> 6) + 0xC0;
		s[1] = (c & 0x3F) + 0x80;
	}
	else if (size == 3)
	{
		s[0] = (c >> 12) + 0xE0;
		s[1] = ((c >> 6) & 0x3F) + 0x80;
		s[2] = (c & 0x3F) + 0x80;
	}
	else
	{
		s[0] = (c >> 18) + 0xF0;
		s[1] = ((c >> 12) & 0x3F) + 0x80;
		s[2] = ((c >> 6) & 0x3F) + 0x80;
		s[3] = (c & 0x3F) + 0x80;
	}
}

int			ft_handle_wchar(wchar_t c, t_data *data, size_t size)
{
	char	s[4];

	ft_memset(s, 0, 5);
	if (c <= 0x7F)
		size = 1;
	else if (c <= 0x7FF)
		size = 2;
	else if (c <= 0xFFFF)
		size = 3;
	else if (c <= 0x10FFFF)
		size = 4;
	else
		size = 0;
	if (size == 0)
		return (-1);
	ft_into_char(c, s, size);
	if (data->minus)
		size = ft_handle_minus(s, data, size);
	else if (data->width_field)
		size = ft_handle_width(s, data, size);
	else
		ft_buffer(s, data, size);
	return (size);
}
