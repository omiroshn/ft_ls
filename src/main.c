/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:59:28 by omiroshn          #+#    #+#             */
/*   Updated: 2018/08/21 21:59:29 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_error(char *dir_name, char *strerror)
{
	if (errno == 2)
		ft_printf("ls: %s: %s\n", dir_name, strerror);
	else if (errno == 13)
	{
		ft_printf("%s:\n", dir_name);
		ft_printf("ls: %s: %s\n", dir_name, strerror);
	}
	else if (errno == 20)
		ft_printf("%s\n", dir_name);
	else
		ft_printf("errno: %d %s\n", errno, strerror);
	return (0);
}

int		print_error_flags(char flag)
{
	ft_printf("ls: illegal option -- %c\n", flag);
	ft_printf("usage: ls [-lRart] [file ...]\n");
	return (-1);
}

int		read_files(t_ft_ls *ls, char *dir_name)
{
	
	DIR				*dir;
	struct dirent	*sd;
	struct stat 	file_stat;

	ls->head = NULL;
	ls->tail = NULL;
	ft_printf("shit\n");
	if (stat(dir_name, &file_stat) < 0)
		return (0);
	ft_printf("Information for %s\n", dir_name);
	ft_printf("---------------------------\n");
	ft_printf("File Size: \t\t%d bytes\n", file_stat.st_size);
	ft_printf("Number of Links: \t%d\n", file_stat.st_nlink);
	ft_printf("File inode: \t\t%d\n", file_stat.st_ino);
	ft_printf("File Permissions: \t");
	ft_printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
	ft_printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
	ft_printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
	ft_printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
	ft_printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
	ft_printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
	ft_printf("\n\n");
	ft_printf("The file %s a symbolic link\n", (S_ISLNK(file_stat.st_mode)) ? "is" : "is not");

	if (!(dir = opendir(dir_name)))
		return (print_error(dir_name, strerror(errno)));
	

	//int num_entries = 0;
	while ((sd = readdir(dir)))
	{
		if (!ls->tail)
			ls->tail = lst_push_back(&ls->head, sd->d_name);
		else
			ls->tail = lst_push_back(&ls->tail, sd->d_name);
		//num_entries++;
	}
	//ft_printf("Num entries: %d\n", num_entries);

	// check if argc > 2
	ft_printf("%s:\n", dir_name);
	lst_print(ls->head);
	lst_free(ls->head);
	closedir(dir);
	return (1);
}

int		main(int argc, char **argv)
{
	t_ft_ls		ls;
	char		*dir_name;
	int			i;
	int			j;
	int			used_flags = 0;

	if (argc < 2)
	{
		dir_name = ".";
		read_files(&ls, dir_name);
	}
	else
	{
		i = 1;
		while (i < argc && !(j = 0))
		{
			dir_name = argv[i];
			if ((dir_name[0] == '-' && dir_name[1] == '-') || dir_name[0] != '-')
				break ;
			while (dir_name[++j])
			{
				if (dir_name[j] == 'l')
					ft_printf("l\n");
				else if (dir_name[j] == 'R')
					ft_printf("R\n");
				else if (dir_name[j] == 'a')
					ft_printf("a\n");
				else if (dir_name[j] == 'r')
					ft_printf("r\n");
				else if (dir_name[j] == 't')
					ft_printf("t\n");
				else if (dir_name[j] != 'l' || dir_name[j] != 'R'
					|| dir_name[j] != 'a' || dir_name[j] != 'r'
					|| dir_name[j] != 't')
					return (print_error_flags(dir_name[j]));
			}
			i++;
			used_flags++;
		}
		if (i == argc)
			read_files(&ls, ".");
		else
		{
			argv = ft_sort_argv(argc - i, argv + (i - 1));
			--i;
			while (i < argc - used_flags)
			{
				dir_name = argv[i];
				ft_printf("%d %d %s\n", i, argc, dir_name);
				if (read_files(&ls, dir_name) && i + 1 < argc - used_flags)
					ft_printf("\n");
				i++;
			}
		}
	}
	return (0);
}
