/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 16:50:22 by omiroshn          #+#    #+#             */
/*   Updated: 2018/08/26 16:50:23 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_llist	*lst_push_back(t_llist **head, char *value)
{
	while (*head)
		head = &(*head)->next;
	*head = malloc(sizeof(t_llist));
	(*head)->name = ft_strdup(value);
	(*head)->next = NULL;
	return (*head);
}

void	lst_print(t_llist *list)
{
	while (list)
	{
		ft_printf("\033[1;34m%s\n\033[0m", list->name);
		list = list->next;
	}
}
