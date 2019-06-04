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

int		print_error(char *name)
{
	if (errno == ENOENT || errno == EACCES)
		ft_dprintf(2, R"ls: %s: %s\n"E, name, strerror(errno));
	else if (errno == ENOTDIR)
		ft_dprintf(2, LG"%s\n"E, name);
	else
		ft_dprintf(2, R"errno: %d %s\n"E, errno, strerror(errno));
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

const char *g_mode = "-rwxrwxrwx";

char	get_file_type(mode_t m)
{
	if (S_ISDIR(m))
		return ('d');
	if (S_ISCHR(m))
		return ('c');
	if (S_ISBLK(m))
		return ('b');
	if (S_ISLNK(m))
		return ('l');
	if (S_ISSOCK(m))
		return ('s');
	if (S_ISFIFO(m))
		return ('p');
	return ('-');
}

char	get_attr(t_file *file)
{
	acl_t		acl;
    acl_entry_t	dummy;
	ssize_t		xattr;
	char		chr;

	xattr = 0;
	acl = NULL;
    acl = acl_get_link_np(file->name, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(file->name, NULL, 0, XATTR_NOFOLLOW);
    if (xattr < 0)
        xattr = 0;

    if (xattr > 0)
        chr = '@';
    else if (acl != NULL)
        chr = '+';
    else
        chr = ' ';
	return (chr);
}

int		numlen(int num)
{
	int len;

	len = 1;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

void	color_print(t_file *file, int width)
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

void	print_time(t_file *file, int *width)
{
	int		i;
	char	**time;

	time = ft_strsplit((g_u ? ctime(&file->st->st_atime)
		: ctime(&file->st->st_mtime)), ' ');
	time[3][5] = 0;
	time[4][4] = 0;

	ft_printf("%-*s %*d %s %2s %5s ", width[2], file->group,
		width[4], file->st->st_size, time[1], time[2],
		time[g_time - file->st->st_mtime > 15780000 ? 4 : 3]);
	i = -1;
	while (time[++i])
		free(time[i]);
	free(time);
}

void	print_ll(t_file *file, int *width)
{
	int		i;
	char	*mode;

	mode = ft_strdup(g_mode);
	mode[0] = get_file_type(file->st->st_mode);
	i = 0;
	while (++i <= 9)
		if (!(file->st->st_mode & (1 << (9 - i))))
			mode[i] = '-';
	ft_printf("%s%c %*d ", mode, get_attr(file), width[3], file->st->st_nlink);
	g_g ? 1 : ft_printf("%-*s  ", width[1], file->owner);
	print_time(file, width);
	color_print(file, 0);
	free(mode);
	file = file->next;
}

void	print_l(t_file *file, int *width, int tot)
{
	int		total;
	t_file	*head;

	head = file;
	if (tot)
	{
		total = 0;
		while (head)
		{
			total += head->st->st_size;
			head = head->next;
		}
		total /= 512;
		if (total)
		{
			total += 2;
			ft_printf("total %d\n", total);
		}
	}
	head = file;
	while (head)
	{
		print_ll(head, width);
		head = head->next;
	}
}

void	print(t_file *list, int width)
{
	int w;
	int c;

	w = g_win.ws_col / (width + 1);
	c = w;
	while (list)
	{
		if (S_ISDIR(list->st->st_mode))
			ft_printf(Y"%-*s"E, width, list->name);
		else if (S_ISLNK(list->st->st_mode))
			ft_printf(P"%-*s"E, width, list->name);
		else if (S_IXUSR & list->st->st_mode)
			ft_printf(R"%-*s"E, width, list->name);
		else
			ft_printf(LG"%-*s"E, width, list->name);
		c--;
		if (c == 0 && (c = w) == w)
			ft_printf("\n");
		else
			ft_printf(" ");
		list = list->next;
	}
	if (c != 0)
		ft_printf("\n");
}

void	fill_stat(t_file *file, int *width)
{
	int len;

	file->owner = ft_strdup(getpwuid(file->st->st_uid)->pw_name);
	if ((len = (int)ft_strlen(file->owner)) > width[1])
		width[1] = len;
	file->group = ft_strdup(getgrgid(file->st->st_gid)->gr_name);
	if ((len = (int)ft_strlen(file->group)) > width[2])
		width[2] = len;
	if ((len = numlen(file->st->st_nlink)) > width[3])
		width[3] = len - 1;
	if ((len = numlen(file->st->st_size)) > width[4])
		width[4] = len;
}

t_file	*create_file(char *path, char *name, int *width)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	if ((int)ft_strlen(file->name) > width[0])
		width[0] = ft_strlen(file->name);
	file->st = malloc(sizeof(struct stat));
	if (!ft_strcmp(file->name, path))
		file->path = ft_strdup(path);
	else
	{
		file->path = malloc(ft_strlen(path) + ft_strlen(file->name) + 2);
		ft_strcpy(file->path, path);
		file->path[ft_strlen(path)] = '/';
		ft_strcpy(&file->path[ft_strlen(path) + 1], file->name);
		file->path[ft_strlen(path) + ft_strlen(file->name) + 1] = 0;
	}
	lstat(file->path, file->st);
	if (g_l)
		fill_stat(file, width);
	return (file);
}

t_file	*open_directory(char *path, int *width)
{
	DIR				*dp;
	struct dirent	*ep;
	t_file			*head;
	t_file			*file;

	if (g_header)
		ft_dprintf(1, W"\n%s:\n"E, path);
	dp = opendir(path);
	if (!dp)
	{
		print_error(path);
		return (NULL);
	}
	head = NULL;
	ft_bzero(width, sizeof(int) * 5);
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

void	go_recurse(t_file *list, int *width)
{
	t_file	*head;

	g_f ? 1 : merge_sort(&list);
	head = list;
	if (g_l)
		print_l(list, width, 1);
	else
		print(list, width[0]);
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
}

t_file	*get_directories(t_file *head, int *width)
{
	t_file *directory;
	t_file *errors;

	directory = NULL;
	errors = NULL;
	while (head)
	{
		if (opendir(head->name))
			lst_push_back(&directory, copy_file(head));
		else if (S_ISREG(head->st->st_mode))
			print_ll(head, width);	
		else
			lst_push_back(&errors, copy_file(head));
		head = head->next;
	}
	while (errors)
	{
		ft_dprintf(1, W"\n%s:\n"E, errors->name);
		print_error(errors->name);
		errors = errors->next;
	}
	return directory;
}

void	ft_ls(char *path)
{
	t_file	*list;
	int		width[5];

	list = open_directory(path, &width[0]);
	go_recurse(list, &width[0]);
}

void	go_through_params(t_file *files, int *width)
{
	t_file	*directories;

	directories = get_directories(files, width);
	g_f ? 1 : merge_sort(&directories);
	while (directories)
	{
		if (S_ISDIR(directories->st->st_mode))
			ft_ls(directories->path);
		directories = directories->next;
	}
}

int		read_parameters(char **file, int ac)
{
	int			i;
	t_file		*head;
	t_file		*new;
	int			header_count;
	int			width[5];

	i = g_stop ? 0 : -1;
	head = NULL;
	header_count = 0;
	ft_bzero(width, sizeof(int) * 5);
	while (++i < ac)
		if (file[i])
		{
			new = create_file(file[i], file[i], width);
			lst_push_back(&head, new);
			header_count++;
		}
	if (header_count > 1)
		g_header = true;
	go_through_params(head, width);
	return (true);
}

void	set_flags(char c)
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
	int		i;
	int		j;

	i = 0;
	time(&g_time);
	ioctl(0, TIOCGWINSZ, &g_win);
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			g_stop = true;
		if (argv[i][0] != '-' || g_stop)
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
