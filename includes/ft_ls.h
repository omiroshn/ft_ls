/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 22:01:39 by omiroshn          #+#    #+#             */
/*   Updated: 2018/08/21 22:01:40 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "colored_str.h"

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/ioctl.h>

bool			g_l;
bool			g_rec;
bool			g_a;
bool			g_r;
bool			g_t;
bool			g_d;
bool			g_u;
bool			g_f;
bool			g_g;
bool			g_stop;
bool			g_noargs;
bool			g_first_dir;
bool			g_header;
time_t			g_time;
struct winsize	g_win;

typedef	struct	s_file
{
	char			*name;
	char			*path;
	char			*owner;
	char			*group;
	struct stat		*st;
	struct s_file	*next;
}				t_file;

typedef struct	s_ls
{
	t_file			*head;
	t_file			*tail;
	struct dirent	*sd;
	struct stat 	file_stat;
}				t_ls;

void	free_file(t_file *file);
t_file	*copy_file(t_file *file);
t_file	*lst_push_back(t_file **head, t_file *file);
t_file	*lst_push_back_p(t_file **head, char *value, struct stat *ds, __uint8_t t);
void	lst_free(t_file *head);
void	lst_print(t_file *list, uint64_t flags);
t_file	*new_list(void const *name);
void	add_to_list(t_file **head, t_file *data);
void	merge_sort(t_file **file);
void	ft_ls(char *path);
void    print_l(t_file *file, int *width, int tot);
void	print_ll(t_file *file, int *width);

#endif
