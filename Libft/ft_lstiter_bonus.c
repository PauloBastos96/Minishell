/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:09:55 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 16:09:12 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates the list ’lst’ and applies the function
’f’ on the content of each node.*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	if (!f)
		return ;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}
