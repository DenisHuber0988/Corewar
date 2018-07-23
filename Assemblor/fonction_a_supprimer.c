/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 09:55:26 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/17 09:58:47 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*void	add_instru(t_champ *begin, t_champ *list, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (space(str[i]) != 1)
		i++;
	while (space(str[i + j]))
	{
		list->arg[check_line(list->code)][j] = str[i + j];
		str[i + j] = ' ';
		j++;
	}
	i = 0;
	while (ft_strcmp(g_op_tab[i].name, (char*)list->arg[check_line(list->code)]\
	) && i < 16)
		i++;
	if (i == 16)
		error(-8);
	else
	{
		begin->str[begin->prog_size] = g_op_tab[i].OPC;
		begin->prog_size += 1;
	}
}*/

/*void	live(t_champ *begin, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 3;
	while (i < j)
	{
		begin->str[begin->prog_size + i] = 0x00;
		i++;
	}
	begin->prog_size += i;
	i = index_arg(str);
	if (str[i] == '%')
	{
		begin->str[begin->prog_size] = ft_atoi(str + i + 1);
		begin->prog_size += 1;
	}
}*/
