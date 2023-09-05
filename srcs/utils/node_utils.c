/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:19:34 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/31 15:52:25 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

// void	insert_front(t_cmd **head, char *cmd)
// {
// 	t_cmd	*new_node;

// 	new_node = malloc(sizeof(t_cmd));
// 	new_node->cmd = create_cmd(cmd);
// 	new_node->next = *head;
// 	new_node->prev = NULL;
// 	if ((*head) != NULL)
// 		(*head)->prev = new_node;
// 	*head = new_node;
// }

// void	insert_end(t_cmd **head, char *cmd)
// {
// 	t_cmd	*new_node;
// 	t_cmd	*temp;

// 	temp = *head;
// 	new_node = malloc(sizeof(t_cmd));
// 	if (new_node == NULL)
// 		return ;
// 	new_node->next = NULL;
// 	if ((*head) == NULL)
// 	{
// 		new_node->prev = NULL;
// 		new_node->cmd = create_cmd(cmd);
// 		*head = new_node;
// 		return ;
// 	}
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = new_node;
// 	new_node->prev = temp;
// 	new_node->cmd = create_cmd(cmd);
// }
