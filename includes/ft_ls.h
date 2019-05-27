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
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>

# define FT_LFLAG 0x1
# define FT_RECUR 0x2
# define FT_ALL 0x4
# define FT_REV 0x8
# define FT_TSORT 0x10

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

typedef	struct	s_file
{
	char			*name;
	struct stat		st;
	struct s_file	*next;
	bool			is_dir;
}				t_file;

typedef struct	s_ls
{
	t_file			*head;
	t_file			*tail;
	struct dirent	*sd;
	struct stat 	file_stat;
}				t_ls;

t_file	*lst_push_back(t_file **head, char *value, struct stat st, __uint8_t t);
void	lst_free(t_file *head);
void	lst_print(t_file *list, uint64_t flags);
t_file	*new_list(void const *name);
void	add_to_list(t_file **head, t_file *data);
void	merge_sort(t_file **file);
void	ft_ls(t_file *files);

#endif
