/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:20:01 by dhuber            #+#    #+#             */
/*   Updated: 2018/04/14 16:45:49 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_liste	*ft_lstmap(t_liste *lst, t_liste *(*f)(t_liste *elem))
{
	t_liste	*new;
	t_liste	*start;

	if (!lst || !f)
		return (NULL);
	start = (f)(lst);
	new = start;
	while (lst->next)
	{
		lst = lst->next;
		new->next = (f)(lst);
		new = new->next;
	}
	return (start);
}
