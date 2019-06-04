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
	new->name = ft_strdup(file->name);
	new->path = ft_strdup(file->path);
	new->owner = ft_strdup(file->owner);
	new->group = ft_strdup(file->group);
	new->st = ft_memalloc(sizeof(struct stat));
	new->st = file->st;
	return new;
}

void	free_file(t_file *file)
{
	free(file->name);
	free(file->path);
	free(file->owner);
	free(file->group);
	free(file->st);
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
