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

	new = (t_file*)malloc(sizeof(t_file));
	new->name = file->name;
	new->path = file->path;
	new->st = file->st;
	new->owner = file->owner;
	new->group = file->group;
	return (new);
}

t_file	*free_list_files(t_file *list_files)
{
	t_file *before;

	while (list_files)
	{
		free(list_files->name);
		free(list_files->path);
		free(list_files->st);
		if (g_l || g_s)
		{
			free(list_files->owner);
			free(list_files->group);
		}
		before = list_files;
		list_files = list_files->next;
		free(before);
	}
	return (NULL);
}
