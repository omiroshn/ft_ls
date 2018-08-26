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

typedef	struct	s_llist
{
	char			*name;
	struct s_llist	*next;
}				t_llist;

t_llist	*lst_push_back(t_llist **head, char *value);
void	lst_print(t_llist *list);

#endif
