/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:24:42 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/23 14:58:16 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Counts the number of nodes in a list.*/
int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*tmp;

	counter = 0;
	tmp = lst;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}
