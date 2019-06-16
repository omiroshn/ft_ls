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
bool			g_s;
bool			g_one;
bool			g_stop;
bool			g_noargs;
bool			g_first_dir;
bool			g_header;
bool			g_firsttime;
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

/*
** main.c
*/
void			ft_ls(char *path);

/*
** list.c
*/
t_file			*lst_push_back(t_file **head, t_file *file);
t_file			*copy_file(t_file *file);
t_file			*free_list_files(t_file *list_files);

/*
** merge_sort.c
*/
void			merge_sort(t_file **file);

/*
** time_sort.c
*/
t_file			*ft_sort_mtime(t_file *root);
t_file			*ft_sort_mtime_r(t_file *root);
t_file			*ft_sort_utime(t_file *root);
t_file			*ft_sort_utime_r(t_file *root);

/*
** open_file.c
*/
t_file			*get_directories(t_file *head, int *width);
t_file			*open_directory(char *path, int *width);
void			go_recurse(t_file *list, int *width);

/*
** print.c
*/
void			print_l(t_file *file, int *width, int tot);
void			print(t_file *list, int width, int width5);

/*
** support.c
*/
void			print_time(t_file *file, int *width);
void			print_header(char *path);
char			get_file_type(mode_t m);
char			get_attr(t_file *file);
int				numlen(int num);

/*
** new_file.c
*/
int				print_error(char *name);
void			print_error_flags(char c);
void			fill_stat(t_file *file, int *width);
t_file			*create_file(char *path, char *name, int *width);

#endif
