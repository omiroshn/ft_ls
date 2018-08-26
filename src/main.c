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

int		print_error(char *dir_name, char *strerror)
{
	if (errno == 2)
		ft_printf("ls: %s: %s\n", dir_name, strerror);
	else if (errno == 13)
	{
		ft_printf("%s:\n", dir_name);
		ft_printf("ls: %s: %s\n", dir_name, strerror);
	}
	else if (errno == 20)
		ft_printf("%s\n", dir_name);
	return (0);
}

int		open_dir(char *dir_name)
{
	DIR				*dir;
	struct dirent	*sd;
	t_llist			*list;
	t_llist			*tmp;

	list = NULL;
	tmp = NULL;
	if (!(dir = opendir(dir_name)))
		return (print_error(dir_name, strerror(errno)));
	while ((sd = readdir(dir)))
	{
		if (!tmp)
			tmp = lst_push_back(&list, sd->d_name);
		else
			tmp = lst_push_back(&tmp, sd->d_name);
	}
	ft_printf("%s:\n", dir_name);
	lst_print(list);
	closedir(dir);
	return (1);
}

int main(int argc, char **argv)
{
	char	*dir_name;
	int		i;

	if (argc < 2)
	{
		dir_name = ".";
		open_dir(dir_name);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			dir_name = argv[i];
			if (open_dir(dir_name) && i + 1 < argc)
				ft_printf("\n");
			i++;
		}
	}
	return (0);
}
