/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:59:28 by omiroshn          #+#    #+#             */
/*   Updated: 2018/08/21 21:59:29 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <sys/types.h>
#include <dirent.h>

typedef	struct	s_llist
{
	char			*name;
	struct s_llist	*next;
}				t_llist;

t_llist	*lst_push_back(t_llist **head, char *value)
{
	while (*head)
		head = &(*head)->next;
	*head = malloc(sizeof(t_llist));
	(*head)->name = ft_strdup(value);
	(*head)->next = NULL;
	return (*head);
}

int main(void)
{
	DIR *dir;
	struct dirent *sd;
	size_t		longest_name = 0;

	t_llist *list = NULL;
	// t_llist	*tmp = NULL;
	// tmp = lst_push_back(&list, "lol");
	// tmp = lst_push_back(&tmp, "kek");
	// tmp = lst_push_back(&tmp, "cheburek");
	// tmp = lst_push_back(&tmp, "allo");

	

	dir = opendir(".");
	if (dir == NULL)
	{
		ft_printf("Error! Unable to open directory.\n");
		exit(-1);
	}
	while ((sd = readdir(dir)))
	{
		// if (longest_name < ft_strlen(sd->d_name))
		// 	longest_name = ft_strlen(sd->d_name);
		lst_push_back(&list, sd->d_name);
	}
	while (list)
	{
		ft_printf("\033[1;34m%s\n\033[0m", list->name);
		list = list->next;
	}
	closedir(dir);

	return (0);
}
// .        ..       .git     Makefile author   ft_ls    includes libft    obj      src 10

// .        .git     author   includes kek2     libft    src
// ..       Makefile ft_ls    kek      kek3     obj                              13

// ft_countwords.c ft_lstdelone.c  ft_memmove.c    ft_strcat.c
// ft_isalnum.c    ft_lstiter.c    ft_memset.c     ft_strchr.c