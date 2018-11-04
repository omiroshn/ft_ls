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

int		print_error(char *dir_name, char *strerror)
{
	if (errno == 2 || errno == 13)
		ft_printf("ls: %s: %s\n", dir_name, strerror);
	else if (errno == 20)
		ft_printf("%s\n", dir_name);
	else
		ft_printf("errno: %d %s\n", errno, strerror);
	return (0);
}

void	print_error_flags(char flag)
{
	ft_printf("ls: illegal option -- %c\n", flag);
	ft_printf("usage: ls [-lRart] [file ...]\n");
	// system("leaks ft_ls");
	exit (-1);
}

int		read_files(t_ft_ls *ls, char *dir_name, uint64_t flags)
{
	DIR				*dir;

	ls->head = NULL;
	ls->tail = NULL;
	if (stat(dir_name, &ls->file_stat) < 0)
		return (print_error(dir_name, strerror(errno)));
	//ft_printf("Information for %s\n", dir_name);
	//ft_printf("---------------------------\n");
	//ft_printf("File Size: \t\t%d bytes\n", ls->file_stat.st_size);
	//ft_printf("Number of Links: \t%d\n", ls->file_stat.st_nlink);
	//ft_printf("File inode: \t\t%d\n", ls->file_stat.st_ino);
	//ft_printf("File Permissions: \t");
	//ft_printf( (S_ISDIR(ls->file_stat.st_mode)) ? "d" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IRUSR) ? "r" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IWUSR) ? "w" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IXUSR) ? "x" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IRGRP) ? "r" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IWGRP) ? "w" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IXGRP) ? "x" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IROTH) ? "r" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IWOTH) ? "w" : "-");
	//ft_printf( (ls->file_stat.st_mode & S_IXOTH) ? "x" : "-");
	//ft_printf("\n\n");
	//ft_printf("The file %s a symbolic link\n", (S_ISLNK(ls->file_stat.st_mode)) ? "is" : "is not");

	if (!(dir = opendir(dir_name)))
		return (print_error(dir_name, strerror(errno)));

	while ((ls->sd = readdir(dir)))
	{
		if (!ls->tail)
			ls->tail = lst_push_back(&ls->head, ls->sd->d_name);
		else
			ls->tail = lst_push_back(&ls->tail, ls->sd->d_name);
	}

	// check if argc > 2
	//ft_printf("%s:\n", dir_name);
	lst_print(ls->head, flags);
	lst_free(ls->head);
	closedir(dir);
	return (1);
}

void		ft_get_flags(char *dir_name, uint64_t *flags)
{
	int	j;

	j = 0;
	while (dir_name[++j])
	{
		if (dir_name[j] == 'l')
			*flags |= FT_LFLAG;
		else if (dir_name[j] == 'R')
			*flags |= FT_RECUR;
		else if (dir_name[j] == 'a')
			*flags |= FT_ALL;
		else if (dir_name[j] == 'r')
			*flags |= FT_REV;
		else if (dir_name[j] == 't')
			*flags |= FT_TSORT;
		else if (dir_name[j] != 'l' || dir_name[j] != 'R'
			|| dir_name[j] != 'a' || dir_name[j] != 'r'
			|| dir_name[j] != 't')
			print_error_flags(dir_name[j]);
		//print_bits(*flags);
	}
}

void	ft_flags(uint64_t *flags, int *i, int argc, char **argv)
{
	(*i) = 0;
	while (++(*i) < argc)
	{
		if ((argv[(*i)][0] == '-' && argv[(*i)][1] == '-') || argv[(*i)][0] != '-')
			break ;
		ft_get_flags(argv[(*i)], flags);
	}
}

void	ft_read_files(uint64_t flags, int argc, char **argv, t_ft_ls *ls)
{
	int i;

	i = 0;
	if (i == argc)
		read_files(ls, ".", flags);
	else
	{
		ft_sort_argv(argc, argv);
		while (i < argc)
		{
			if (read_files(ls, argv[i], flags))
				ft_printf("\n");
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
	t_ft_ls		ls;
	int			i;
	uint64_t	flags;

	flags = 0;
	if (argc < 2)
		read_files(&ls, ".", flags);
	else
	{
		ft_flags(&flags, &i, argc, argv);
		ft_read_files(flags, argc - i, argv + i, &ls);
	}
	return (0);
}
