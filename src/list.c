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

t_file	*lst_push_back(t_file **head, char *value)
{
	while (*head)
		head = &(*head)->next;
	*head = malloc(sizeof(t_file));
	(*head)->name = ft_strdup(value);
	(*head)->next = NULL;
	return (*head);
}

void	lst_free(t_file *head)
{
	t_file *tmp;

	while (head)
	{
		free(head->name);
		tmp = head;
		free(tmp);
		head = head->next;
	}
	free(head);
}

t_file	*new_list(void const *name)
{
	t_file	*file;

	file = ft_memalloc(sizeof(t_file));
	if (name == NULL)
	{
		file->name = NULL;
		file->next = NULL;
	}
	else
	{
		file->name = ft_strdup(name);
		file->next = NULL;
	}
	return (file);
}

void	add_to_list(t_file **head, t_file *data)
{
	t_file *file;
	
	file = data;
	if (*head == NULL)
	{
		*head = data;
		return;
	}
	while ((*head)->next)
		head = &(*head)->next;
	(*head)->next = data;
}