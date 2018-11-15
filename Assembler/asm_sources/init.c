/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:50:03 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:06:43 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	initialize struct champ
*/

t_champ		*init_champ(void)
{
	t_champ	*begin;
	int		i;

	i = 0;
	if (!(begin = (t_champ*)malloc(sizeof(t_champ))))
		error(-5);
	ft_bzero(begin->label, 102);
	ft_bzero(begin->arg1, 100);
	while (i < 100)
	{
		ft_bzero(begin->sec[i], 3);
		ft_bzero(begin->tmp[i], 100);
		ft_bzero(begin->arg[i], 100);
		begin->code[i] = 0;
		begin->tmplen[i] = 0;
		begin->tmp_prog_size[i] = 0;
		i++;
	}
	begin->len = 0;
	begin->file = NULL;
	begin->prog_size = 0;
	begin->adr = 0;
	ft_bzero(begin->str, CHAMP_MAX_SIZE);
	begin->next = NULL;
	return (begin);
}

/*
**	initialize struct header
*/

t_header	*init_header(void)
{
	t_header	*head;

	if (!(head = (t_header*)malloc(sizeof(t_header))))
		error(-5);
	ft_bzero(head->magic, 4);
	ft_bzero(head->name, PROG_NAME_LENGTH + 4);
	ft_bzero(head->comment, COMMENT_LENGTH + 4);
	head->prog_size = 0;
	return (head);
}

/*
**	empty the struct header and free the list champ
*/

void		del_list(t_champ **begin, t_header *head)
{
	t_champ	*list;

	while (*begin)
	{
		list = (*begin)->next;
		ft_memdel((void **)&(*begin)->file);
		ft_memdel((void **)begin);
		*begin = list;
	}
	ft_bzero(head->magic, 4);
	ft_bzero(head->name, PROG_NAME_LENGTH + 4);
	ft_bzero(head->comment, COMMENT_LENGTH + 4);
	head->prog_size = 0;
}
