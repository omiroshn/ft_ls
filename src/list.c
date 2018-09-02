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

void	lst_free(t_llist *head)
{
	t_llist *tmp;

	while (head)
	{
		free(head->name);
		tmp = head;
		free(tmp);
		head = head->next;
	}
	free(head);
}

void	lst_print(t_llist *list, uint64_t flags)
{	
	while (list)
	{
		if (IS_ALL(flags))
		{
			ft_printf(ANSI_COLOR_BLUE_BOLD
			"%s"ANSI_COLOR_RESET"\n", list->name);
		}
		else
		{
			if (list->name[0] != '.')
			{
				ft_printf(ANSI_COLOR_BLUE_BOLD
				"%s"ANSI_COLOR_RESET"\n", list->name);
			}
		}
		list = list->next;
	}
}
