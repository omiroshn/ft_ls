/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:59:28 by omiroshn          #+#    #+#             */
/*   Updated: 2018/10/30 18:52:56 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_flags(char c)
{
	if (c == 'l')
		g_l = true;
	else if (c == 'R')
		g_rec = true;
	else if (c == 'a')
		g_a = true;
	else if (c == 'r')
		g_r = true;
	else if (c == 't')
		g_t = true;
	else if (c == 'u')
		g_u = true;
	else if (c == 'f')
		g_f = true;
	else if (c == 'g')
		g_g = true;
	else if (c == 'd')
		g_d = true;
	else if (c == 's')
		g_s = true;
	else if (c == '1')
		g_one = true;
	else
		print_error_flags(c);
}

void		ft_ls(char *path)
{
	t_file	*list;
	int		width[6];

	list = open_directory(path, &width[0]);
	go_recurse(list, &width[0]);
}

static void	go_through_params(t_file *files, int *width)
{
	t_file	*directories;
	t_file	*cpy;

	directories = get_directories(files, width);
	g_f ? 1 : merge_sort(&directories);
	cpy = directories;
	while (directories)
	{
		if (S_ISDIR(directories->st->st_mode))
			ft_ls(directories->path);
		else if (g_one && S_ISLNK(directories->st->st_mode))
			ft_ls(directories->path);
		directories = directories->next;
	}
	free_list_files(cpy);
}

static int	read_parameters(char **file, int ac)
{
	int			i;
	t_file		*head;
	int			header_count;
	int			width[6];
	struct stat st;

	i = g_stop ? 0 : -1;
	head = NULL;
	header_count = 0;
	ft_bzero(width, sizeof(int) * 6);
	while (++i < ac)
		if (file[i] && (++header_count))
		{
			if (lstat(file[i], &st) == -1)
				print_error(file[i]);
			else
				lst_push_back(&head, create_file(file[i], file[i], width));
		}
	if (!head && g_stop)
		ft_ls(".");
	if (header_count > 1)
		g_header = true;
	go_through_params(head, width);
	return (true);
}

int			main(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	g_firsttime = true;
	time(&g_time);
	ioctl(0, TIOCGWINSZ, &g_win);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "--"))
			g_stop = true;
		if (argv[i][0] != '-' || g_stop || !ft_strcmp(argv[i], "-"))
			return (read_parameters(&argv[i], argc - i));
		j = 0;
		while (argv[i][++j])
			set_flags(argv[i][j]);
		g_f ? g_a = true : 1;
		g_g ? g_l = true : 1;
	}
	g_noargs = true;
	ft_ls(".");
	return (0);
}
