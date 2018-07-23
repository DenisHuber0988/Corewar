/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:01:20 by jauplat           #+#    #+#             */
/*   Updated: 2018/07/21 15:39:07 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

void	translate(t_header *head, t_champ *begin)
{
	head->prog_size = (0xff & begin->prog_size) << 24;
	head->prog_size += (0xff00 & begin->prog_size) << 8;
	head->prog_size += (0xff0000 & begin->prog_size) >> 8;
	head->prog_size += (0xff000000 & begin->prog_size) >> 24;
}

void	write_champ(int j, t_header *head, t_champ *begin)
{
	if (!begin->str[0])
		error(-14);
	ft_putstr("Writing output program to ");
	ft_putendl(begin->file);
	translate(head, begin);
	write(j, head, sizeof(t_header));
	write(j, begin->str, begin->prog_size);
}

int		main(int argc, char **argv)
{
	t_champ		*begin;
	t_header	*head;
	int			i;
	int			j;

	i = 1;
	begin = NULL;
	head = init_header();
	while (i < argc)
	{
		ft_putendl(argv[i]);
		begin = init_champ();
		get_file(begin, head, argv[i]);
		if ((j = open(begin->file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) <= 0)
			return (0);
		write_champ(j, head, begin);
		del_list(&begin, head);
		i++;
	}
	free(head);
	return (0);
}
