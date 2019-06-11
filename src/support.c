/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:26:32 by omiroshn          #+#    #+#             */
/*   Updated: 2019/06/11 18:26:33 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_time(t_file *file, int *width)
{
	int		i;
	char	**time;

	time = ft_strsplit((g_u ? ctime(&file->st->st_atime)
		: ctime(&file->st->st_mtime)), ' ');
	time[3][5] = 0;
	if (ft_strlen(time[4]) == 5 && (i = 5))
		time[4][4] = 0;
	else if ((i = 6))
		time[4][5] = 0;
	ft_printf("%-*s  %*d %s %2s %*s ", width[2], file->group,
		width[4], file->st->st_size, time[1], time[2], i,
		time[g_time - file->st->st_mtime > 13046400
		|| g_time - file->st->st_mtime < 0 ? 4 : 3]);
	i = -1;
	while (time[++i])
		free(time[i]);
	free(time);
}

void	print_header(char *path)
{
	if (g_firsttime)
	{
		ft_dprintf(1, W"%s:\n"E, path);
		g_firsttime = false;
	}
	else
		ft_dprintf(1, W"\n%s:\n"E, path);
}

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
	if (acl || acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(file->name, NULL, 0, XATTR_NOFOLLOW);
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

	len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}
