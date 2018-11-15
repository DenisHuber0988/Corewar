/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:01:20 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 14:59:28 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	translate a prog_size little_endian to big_endian
*/

void	translate(t_header *head, t_champ *begin)
{
	head->prog_size = (unsigned int)(0xff & begin->prog_size) << 24;
	head->prog_size += (unsigned int)(0xff00 & begin->prog_size) << 8;
	head->prog_size += (unsigned int)(0xff0000 & begin->prog_size) >> 8;
	head->prog_size += (0xff000000 & (unsigned int)begin->prog_size) >> 24;
}

/*
**	create a file .cor
**	write header and program to the file ".cor"
*/

int		write_champ(t_header *head, t_champ *begin)
{
	int		j;

	if ((j = open(begin->file, O_WRONLY | O_CREAT | O_TRUNC, 0600)) <= 0)
	{
		del_list(&begin, head);
		free(head);
		return (1);
	}
	ft_putstr("Writing output program to ");
	ft_putendl(begin->file);
	translate(head, begin);
	write(j, head, sizeof(t_header));
	write(j, begin->str, (size_t)begin->prog_size);
	return (0);
}

/*
**	get a champion ".s" and treatment for this
*/

int		main(int argc, char **argv)
{
	t_champ		*begin;
	t_header	*head;
	int			i;

	i = 1;
	begin = NULL;
	head = init_header();
	while (i < argc)
	{
		ft_putendl(argv[i]);
		begin = init_champ();
		get_file(begin, head, argv[i]);
		if (!begin->str[0] || begin->prog_size <= 2)
			error(-14);
		if (write_champ(head, begin))
			return (0);
		del_list(&begin, head);
		i++;
	}
	free(head);
	return (0);
}
