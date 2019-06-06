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

t_file	*lst_push_back(t_file **head, t_file *file)
{
	while (*head)
		head = &(*head)->next;
	(*head) = file;
	(*head)->next = NULL;
	return (*head);
}

t_file	*copy_file(t_file *file)
{
	t_file *new;

	new = ft_memalloc(sizeof(t_file));
	new->name = file->name;
	new->path = file->path;
	new->st = file->st;
	new->owner = file->owner;
	new->group = file->group;
	return new;
}

void	free_file(t_file *file)
{
	free(file->name);
	free(file->path);
	free(file->st);
	free(file->owner);
	free(file->group);
}

void	lst_free(t_file *head)
{
	t_file *tmp;

	while (head)
	{
		tmp = head;
		free(tmp->name);
		if (g_l || g_s)
		{
			free(tmp->group);
			free(tmp->owner);
		}
		free(tmp->path);
		free(tmp->st);
		free(tmp);
		head = head->next;
	}
	free(head);
}