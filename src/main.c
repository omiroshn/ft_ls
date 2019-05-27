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

//ls -1R . 1 2 3 4 5 author includes ft_ls denied

#include "ft_ls.h"

int		print_error(char *dir_name)
{
	if (errno == ENOENT || errno == EACCES)
		ft_dprintf(1, "ls: %s: %s\n", dir_name, strerror(errno));
	else if (errno == ENOTDIR)
		ft_dprintf(1, "%s\n", dir_name);
	else
		ft_dprintf(1, "errno: %d %s\n", errno, strerror(errno));
	return (0);
}

void	print_error_flags(char flag)
{
	ft_dprintf(1, "ls: illegal option -- %c\n", flag);
	ft_dprintf(1, "usage: ls [-lRart] [file ...]\n");
	// system("leaks ft_ls");
	exit(-1);
}

void	print_lst(t_file *file)
{
	while (file)
	{
		ft_dprintf(1, "%s\n", file->name);
		file = file->next;
	}
}

t_file	*get_directories(t_file *head)
{
	t_file *directory;

	directory = NULL;
	while (head)
	{
		if (!(opendir(head->name)))
			if (errno != EACCES)
				print_error(head->name);
			else
				add_to_list(&directory, new_list(head->name));
		else
			add_to_list(&directory, new_list(head->name));
		head = head->next;
	}
	return directory;
}

t_file	*get_directories_from_list(t_file *list)
{
	t_file *new;
	t_file *tail;

	new = NULL;
	tail = NULL;
	while (list)
	{
		if (list->is_dir)
		{
			if (new == NULL)
			{
				new = ft_memalloc(sizeof(t_file));
				new->name = list->name;
				new->next = NULL;
				tail = new;
			}
			else
			{
				tail->next = ft_memalloc(sizeof(t_file));
				tail = tail->next;
				tail->name = list->name;
				tail->next = NULL;
			}
		}
		list = list->next;
	}
	return new;
}

void	open_directory(char *path) {
    DIR				*dp;
	struct dirent	*ep;
	struct stat		st;
    char			newdir[512];
	t_file			*list;
	t_file			*directories;

	list = NULL;
	directories = NULL;
	dp = opendir(path);    
	
	if (!dp) {
		if ((path[0] != '.' || path[1]) && (path[0] != '.' || path[1] != '.'))
			ft_dprintf(1, "\n%s:\n", path);
        print_error(path);
        return;
    }
	if ((path[0] != '.' || path[1]) && (path[0] != '.' || path[1] != '.'))
		ft_dprintf(1, "\n%s:\n", path);

    while ((ep = readdir(dp)))
	{
		stat(ep->d_name, &st);
		lst_push_back(&list, ep->d_name, st, ep->d_type);
	}
	merge_sort(&list);
	directories = get_directories_from_list(list);
	while (list)
	{
		if (g_a)
			ft_dprintf(1, "%s\n", list->name);
		else
		{
			if (ft_strncmp(list->name, ".", 1))
				ft_dprintf(1, "%s\n", list->name);
		}
		list = list->next;
	}
	closedir(dp);
	merge_sort(&directories);
	while (directories)
	{
		if (g_rec && (ft_strncmp(directories->name, ".", 1) || g_a))
		{
			if ((directories->name[0] != '.' || directories->name[1])
			&& (directories->name[0] != '.' || directories->name[1] != '.'))
			{
				char *tmp1 = ft_strjoin(path, "/");
				char *tmp2 = ft_strjoin(tmp1, directories->name);
				open_directory(tmp2);
				free(tmp1);
				free(tmp2);
			}
		}
		directories = directories->next;
	}
}

void	ft_ls(t_file *files)
{
	t_file	*directories;

	directories = get_directories(files);
	merge_sort(&directories);
	while (directories)
	{
		open_directory(directories->name);
		directories = directories->next;
	}
}

int	read_input_pars(char **file, int ac)
{
	int			i;
	t_file		*files;
	struct stat	ds;

	i = g_stop ? 0 : -1;
	while (++i < ac)
		if (file[i])
		{
			stat(file[i], &ds);
			lst_push_back(&files, file[i], ds, 0);
		}
	ft_ls(files);
	return (true);
}

void	set_flag(char c)
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
	else
	{
		ft_dprintf(1, "usage: ft_ls [-lRartufgd]\n");
		exit(1);
	}
}

int		main(int argc, char **argv)
{
	t_ls	ls;
	int		i;
	int		j;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			g_stop = true;
		if (argv[i][0] != '-' || g_stop)
			return (read_input_pars(&argv[i], argc - i));
		j = 0;
		while (argv[i][++j])
			set_flag(argv[i][j]);
		if (g_f)
			g_a = true;
		if (g_g)
			g_l = true;
	}
	g_noargs = true;
	open_directory(".");
	return (0);
}
