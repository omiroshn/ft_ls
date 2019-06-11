/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:27:46 by omiroshn          #+#    #+#             */
/*   Updated: 2019/06/11 18:27:46 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_error_flags(char c)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", c);
	ft_dprintf(2, "usage: ft_ls [-lRartufgds] [file ...]\n");
	exit(1);
}

void	fill_stat(t_file *file, int *width)
{
	int len;

	file->owner = getpwuid(file->st->st_uid) ?
	ft_strdup(getpwuid(file->st->st_uid)->pw_name) : ft_strdup("Unknown");
	if ((len = (int)ft_strlen(file->owner)) > width[1])
		width[1] = len;
	file->group = ft_strdup(getgrgid(file->st->st_gid)->gr_name);
	if ((len = (int)ft_strlen(file->group)) > width[2])
		width[2] = len;
	if ((len = numlen(file->st->st_nlink)) > width[3])
		width[3] = len;
	if ((len = numlen(file->st->st_size)) > width[4])
		width[4] = len;
	if ((len = numlen(file->st->st_blocks)) > width[5])
		width[5] = len;
}

t_file	*create_file(char *path, char *name, int *width)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->next = NULL;
	if ((int)ft_strlen(file->name) > width[0])
		width[0] = ft_strlen(file->name);
	file->st = (struct stat *)malloc(sizeof(struct stat));
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
	if (g_l || g_s)
		fill_stat(file, width);
	return (file);
}
