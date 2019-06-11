/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:16:52 by omiroshn          #+#    #+#             */
/*   Updated: 2019/06/11 18:16:52 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	handle_files(t_file *files, int *width)
{
	g_f ? 1 : merge_sort(&files);
	if (g_l)
		print_l(files, width, 0);
	else
		g_one ? print(files, 0, width[5]) : print(files, width[0], width[5]);
	free_list_files(files);
}

static void	handle_errors(t_file *errors)
{
	while (errors)
	{
		if (g_header)
			print_header(errors->name);
		print_error(errors->name);
		errors = errors->next;
	}
}

t_file		*get_directories(t_file *head, int *width)
{
	t_file	*directory;
	t_file	*files;
	t_file	*errors;
	DIR		*d;

	directory = NULL;
	errors = NULL;
	files = NULL;
	while (head)
	{
		if ((d = opendir(head->name)))
		{
			lst_push_back(&directory, copy_file(head));
			closedir(d);
		}
		else if (S_ISREG(head->st->st_mode) || S_ISLNK(head->st->st_mode))
			lst_push_back(&files, copy_file(head));
		else
			lst_push_back(&errors, copy_file(head));
		head = head->next;
	}
	files ? handle_files(files, width) : 0;
	handle_errors(errors);
	free_list_files(errors);
	return (directory);
}

t_file		*open_directory(char *path, int *width)
{
	DIR				*dp;
	struct dirent	*ep;
	t_file			*head;
	t_file			*file;

	if (g_header)
		print_header(path);
	dp = opendir(path);
	if (!dp)
	{
		print_error(path);
		return (NULL);
	}
	head = NULL;
	ft_bzero(width, sizeof(int) * 6);
	while ((ep = readdir(dp)))
	{
		if (!g_a && ep->d_name[0] == '.')
			continue ;
		file = create_file(path, ep->d_name, width);
		lst_push_back(&head, file);
	}
	closedir(dp);
	return (head);
}

void		go_recurse(t_file *list, int *width)
{
	t_file	*head;
	t_file	*tmp;

	g_f ? 1 : merge_sort(&list);
	head = list;
	tmp = head;
	if (g_l)
		print_l(list, width, 1);
	else
		g_one ? print(list, 0, width[5]) : print(list, width[0], width[5]);
	if (g_rec)
	{
		g_header = true;
		while (head)
		{
			if (ft_strcmp(head->name, ".") && ft_strcmp(head->name, "..")
				&& S_ISDIR(head->st->st_mode))
				ft_ls(head->path);
			head = head->next;
		}
	}
	free_list_files(list);
}
