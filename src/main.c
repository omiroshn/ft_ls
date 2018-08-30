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

int		read_files(char *dir_name)
{
	DIR				*dir;
	struct dirent	*sd;
	t_llist			*head;
	t_llist			*tail;
	struct stat 	file_stat;

	head = NULL;
	tail = NULL;
	if (!(dir = opendir(dir_name)))
		return (print_error(dir_name, strerror(errno)));
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

	//int num_entries = 0;
	while ((sd = readdir(dir)))
	{
		if (!tail)
			tail = lst_push_back(&head, sd->d_name);
		else
			tail = lst_push_back(&tail, sd->d_name);
		//num_entries++;
	}
	//ft_printf("Num entries: %d\n", num_entries);

	//check if argc > 2
	ft_printf("%s:\n", dir_name);
	lst_print(head);
	lst_free(head);
	closedir(dir);
	return (1);
}

int		main(int argc, char **argv)
{
	char	*dir_name;
	int		i;

	if (argc < 2)
	{
		dir_name = ".";
		read_files(dir_name);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			dir_name = argv[i];
			if (read_files(dir_name) && i + 1 < argc)
				ft_printf("\n");
			i++;
		}
	}
	return (0);
}
