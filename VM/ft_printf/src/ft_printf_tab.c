/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:37:12 by dhuber            #+#    #+#             */
/*   Updated: 2018/02/27 17:33:14 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

t_func	g_list[] =
{
	{&ft_noflag, "%"},
	{&ft_flag_b, "b"},
	{&ft_flag_b, "B"},
	{&ft_flag_c, "c"},
	{&ft_flag_c, "C"},
	{&ft_flag_d, "d"},
	{&ft_flag_d, "D"},
	{&ft_flag_f, "f"},
	{&ft_flag_f, "F"},
	{&ft_flag_s, "s"},
	{&ft_flag_s, "S"},
	{&ft_flag_o, "o"},
	{&ft_flag_o, "O"},
	{&ft_flag_p, "p"},
	{&ft_flag_u, "u"},
	{&ft_flag_u, "U"},
	{&ft_flag_x, "x"},
	{&ft_flag_capx, "X"},
	{&ft_flag_d, "i"},
	{&ft_wrong, {-1}}
};

int		ft_printf_conversion(char **format, va_list *arg,
		t_data *data, size_t ret)
{
	int			i;
	int			tmp_ret;
	int			*flag_n;

	if (**format == '\0')
		return (-1);
	i = 0;
	if (**format == 'n')
	{
		tmp_ret = ret;
		flag_n = va_arg(*arg, int*);
		*flag_n = tmp_ret;
		return (0);
	}
	while (g_list[i].key[0] != -1)
	{
		if (g_list[i].key[0] == **format)
			return (g_list[i].ptr_func(format, arg, data));
		i++;
	}
	return (g_list[i].ptr_func(format, arg, data));
}
