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

# define FT_LFLAG 0x1
# define FT_RECUR 0x2
# define FT_ALL 0x4
# define FT_REV 0x8
# define FT_TSORT 0x10

# define IS_LFLAG(flags) ((flags) & 1)
# define IS_RECUR(flags) ((flags >> 1) & 1)
# define IS_ALL(flags) ((flags >> 2) & 1)
# define IS_REV(flags) ((flags >> 3) & 1)
# define IS_TSORT(flags) ((flags >> 4) & 1)

typedef	struct	s_llist
{
	char			*name;
	struct s_llist	*next;
}				t_llist;

typedef struct	s_ft_ls
{
	t_llist			*head;
	t_llist			*tail;
	struct dirent	*sd;
	struct stat 	file_stat;
}				t_ft_ls;

t_llist	*lst_push_back(t_llist **head, char *value);
void	lst_free(t_llist *head);
void	lst_print(t_llist *list, uint64_t flags);

#endif
