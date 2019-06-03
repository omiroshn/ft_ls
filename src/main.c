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
		ft_dprintf(1, R"ls: %s: %s\n"E, dir_name, strerror(errno));
	else if (errno == ENOTDIR)
		ft_dprintf(1, R"%s\n"E, dir_name);
	else
		ft_dprintf(1, R"errno: %d %s\n"E, errno, strerror(errno));
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

void	print_l(t_file *file)
{
	int		i;
	char *mode;

	while (file)
	{
		mode = ft_strdup(g_mode);
		mode[0] = get_file_type(file->st.st_mode);
		
		i = 0;
		while (++i < 9)
			if (!(file->st.st_mode & (1 << (9 - i))))
				mode[i] = '-';
		int width = 2;
		ft_printf("%s%c %*d ", mode, get_attr(file), width, file->st.st_nlink);
		g_g ? 1 : ft_printf("%-*s  ", width, getpwuid(file->st.st_uid)->pw_name);
		ft_printf("%s\n", file->name);
		free(mode);
		file = file->next;
	}
}

void	print(t_file *list, int longest)
{
	// ft_printf("%d %d\n", longest, g_win.ws_col);
	int w = g_win.ws_col / (longest + 1);
	int c = w;
	while (list)
	{
		// ft_printf("%o ", list->st.st_mode);
		// if (S_ISDIR(list->st.st_mode))
		// 	ft_printf(Y"%-*s"E, longest, list->name);
		// else if (S_IXUSR & list->st.st_mode)
		// 	ft_printf(R"%-*s"E, longest, list->name);
		// else
			ft_printf("%-*s", longest, list->name);
		c--;
		if (c == 0 && (c = w) == w)
			ft_printf("\n");
		else
			ft_printf(" ");
		// ft_printf("\n");
		list = list->next;
	}
	if (c != 0)
		ft_printf("\n");
}

int		open_directory(char *path)
{
    DIR				*dp;
	struct dirent	*ep;
	struct stat		st;
    char			newdir[512];
	t_file			*list;
	t_file			*directories;

	list = NULL;
	directories = NULL;

	if (g_header)
		ft_dprintf(1, W"\n%s:\n"E, path);

	dp = opendir(path);
	if (!dp)
        return (print_error(path));

	int longest = 0;
    while ((ep = readdir(dp)))
	{
		if (!g_a && ep->d_name[0] == '.')
			continue ;
		lstat(ep->d_name, &st);
		if ((int)ft_strlen(ep->d_name) > longest)
			longest = ft_strlen(ep->d_name);
		lst_push_back(&list, ep->d_name, st, ep->d_type);
	}
	closedir(dp);

	merge_sort(&list);
	if (g_l) print_l(list);
	else print(list, longest);
	directories = get_directories_from_list(list);
	merge_sort(&directories);
	if (g_rec)
	{
		g_header = true;
		while (directories)
		{
			if (ft_strcmp(directories->name, ".") && ft_strcmp(directories->name, ".."))
			{
				char *tmp1 = ft_strjoin(path, "/");
				char *tmp2 = ft_strjoin(tmp1, directories->name);
				open_directory(tmp2);
				free(tmp1);
				free(tmp2);
			}
			directories = directories->next;
		}
	}
	return (true);
}

int	read_input_pars(char **file, int ac)
{
	int			i;
	t_file		*files;
	t_file		*directories;
	struct stat	ds;
	int			header_count;

	i = g_stop ? 0 : -1;
	files = NULL;
	header_count = 0;
	while (++i < ac)
		if (file[i])
		{
			lstat(file[i], &ds);
			lst_push_back(&files, file[i], ds, 0);
			header_count++;
		}
	if (header_count > 1)
		g_header = true;
	directories = get_directories(files);
	merge_sort(&directories);
	while (directories)
	{
		open_directory(directories->name);
		directories = directories->next;
	}
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
//LP - for links
//R - errors
//B - dirs
//LR - binaries

int		main(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	// ft_printf(LR"LRLRLR"LY"LYLYLY"LG"LGLGLG"LB"LBLBLB"LP"LPLPLP"R"RRR"O"OOO"Y"YYY"G"GGG"B"BBB"P"PPP\n"E);
	// exit(1);
	ioctl(0, TIOCGWINSZ, &g_win);
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
