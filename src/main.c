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

int		print_error(char *dir_name)
{
	if (errno == 2 || errno == 13)
		ft_dprintf(1, "ls: %s: %s\n", dir_name, strerror(errno));
	else if (errno == 20)
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

// void get_files(char *dir_name)
// {
// 	struct dirent	*sd;

// 	sd = readdir(dir_name);
// }

void ft_ls(char *dir_name)
{
	// get_files(dir_name);
	// ft_dprintf(1, "%s\n", dir_name);
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

t_file	*get_files_from_dir(DIR *d)
{
	t_file			*files;
	struct dirent	*dir;

	files = NULL;
	while ((dir = readdir(d)) != NULL)
		add_to_list(&files, new_list(dir->d_name));
	return files;
}

void	go_through_directories(t_file *directories)
{
	DIR				*d;
	t_file			*files;

	while (directories)
	{
		ft_dprintf(1, "\n%s:\n", directories->name);
		if ((d = opendir(directories->name)))
		{		
			files = get_files_from_dir(d);
			merge_sort(&files);
			print_lst(files);
			closedir(d);
		}
		else
			print_error(directories->name);
		directories = directories->next;
	}
}

int	read_input_pars(char **file, int ac)
{
	int		i;
	DIR		*d;
	t_file	*files;
	t_file	*directories;

	i = g_stop ? 0 : -1;
	while (++i < ac)
		if (file[i])
			lst_push_back(&files, file[i]);
	directories = get_directories(files);
	merge_sort(&files);
	merge_sort(&directories);
	go_through_directories(directories);
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
	char	*base;

	i = 0;
	base = ".";
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
	ft_ls(base);
	return (0);
}
