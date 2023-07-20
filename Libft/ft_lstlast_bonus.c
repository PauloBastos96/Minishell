/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:00:41 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/19 15:41:07 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns the last node of the list*/
t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
