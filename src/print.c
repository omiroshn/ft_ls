/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:25:52 by omiroshn          #+#    #+#             */
/*   Updated: 2019/06/11 18:25:52 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

const char *g_mode = "-rwxrwxrwx";

static void		color_print_l(t_file *file, int width)
{
	int		i;
	char	buf[NAME_MAX];

	if (S_ISDIR(file->st->st_mode))
		ft_printf(Y"%-*s\n"E, width, file->name);
	else if (S_ISLNK(file->st->st_mode))
	{
		i = readlink(file->path, buf, NAME_MAX);
		buf[i] = 0;
		ft_printf(P"%-*s"E LG" -> %s\n"E, width, file->name, buf);
	}
	else if (S_IXUSR & file->st->st_mode)
		ft_printf(R"%-*s\n"E, width, file->name);
	else
		ft_printf(LG"%-*s\n"E, width, file->name);
}

static void		color_print(t_file *file, int width)
{
	if (S_ISDIR(file->st->st_mode))
		ft_printf(Y"%-*s"E, width, file->name);
	else if (S_ISLNK(file->st->st_mode))
		ft_printf(P"%-*s"E, width, file->name);
	else if (S_IXUSR & file->st->st_mode)
		ft_printf(R"%-*s"E, width, file->name);
	else
		ft_printf(LG"%-*s"E, width, file->name);
}

static void		print_ll(t_file *file, int *width)
{
	int		i;
	char	*mode;

	g_firsttime = false;
	mode = ft_strdup(g_mode);
	mode[0] = get_file_type(file->st->st_mode);
	i = 0;
	while (++i <= 9)
		if (!(file->st->st_mode & (1 << (9 - i))))
			mode[i] = '-';
	if (g_s)
		ft_printf("%*d ", width[5], file->st->st_blocks);
	ft_printf("%s%c %*d ", mode, get_attr(file), width[3], file->st->st_nlink);
	g_g ? 1 : ft_printf("%-*s  ", width[1], file->owner);
	print_time(file, width);
	color_print_l(file, 0);
	free(mode);
}

void			print_l(t_file *file, int *width, int tot)
{
	int		total;
	t_file	*head;
	int		empty;

	if (tot)
	{
		head = file;
		empty = false;
		total = 0;
		if (!head)
			empty = true;
		while (head)
		{
			total += head->st->st_blocks;
			head = head->next;
		}
		empty ? 1 : ft_printf("total %d\n", total);
	}
	head = file;
	while (head)
	{
		print_ll(head, width);
		head = head->next;
	}
}

void			print(t_file *list, int width, int width5)
{
	int w;
	int c;

	w = g_win.ws_col / (width + width5 + 1);
	c = w;
	g_firsttime = false;
	while (list)
	{
		if (g_s)
			ft_printf("%*d ", width5, list->st->st_blocks);
		color_print(list, width);
		c--;
		if (g_one || (c == 0 && (c = w) == w))
			write(1, "\n", 1);
		else
		{
			if (list->next == NULL)
				write(1, "\n", 1);
			else
				write(1, " ", 1);
		}
		list = list->next;
	}
}
