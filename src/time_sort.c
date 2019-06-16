/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 16:24:58 by omiroshn          #+#    #+#             */
/*   Updated: 2019/06/16 16:24:59 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ft_sort_mtime(t_file *root)
{
	t_file	*n_r;
	t_file	*n;
	t_file	*cur;

	n_r = NULL;
	while (root)
	{
		n = root;
		root = root->next;
		if (!n_r || n->st->st_mtimespec.tv_sec > n_r->st->st_mtimespec.tv_sec)
		{
			n->next = n_r;
			n_r = n;
		}
		else
		{
			cur = n_r;
			while (cur->next && n->st->st_mtimespec.tv_sec <=
								cur->next->st->st_mtimespec.tv_sec)
				cur = cur->next;
			n->next = cur->next;
			cur->next = n;
		}
	}
	return (n_r);
}

t_file	*ft_sort_mtime_r(t_file *root)
{
	t_file	*n_r;
	t_file	*n;
	t_file	*cur;

	n_r = NULL;
	while (root)
	{
		n = root;
		root = root->next;
		if (!n_r || n->st->st_mtimespec.tv_sec < n_r->st->st_mtimespec.tv_sec)
		{
			n->next = n_r;
			n_r = n;
		}
		else
		{
			cur = n_r;
			while (cur->next && n->st->st_mtimespec.tv_sec >=
								cur->next->st->st_mtimespec.tv_sec)
				cur = cur->next;
			n->next = cur->next;
			cur->next = n;
		}
	}
	return (n_r);
}

t_file	*ft_sort_utime(t_file *root)
{
	t_file	*n_r;
	t_file	*n;
	t_file	*cur;

	n_r = NULL;
	while (root)
	{
		n = root;
		root = root->next;
		if (!n_r || n->st->st_atimespec.tv_sec > n_r->st->st_atimespec.tv_sec)
		{
			n->next = n_r;
			n_r = n;
		}
		else
		{
			cur = n_r;
			while (cur->next && n->st->st_atimespec.tv_sec <=
								cur->next->st->st_atimespec.tv_sec)
				cur = cur->next;
			n->next = cur->next;
			cur->next = n;
		}
	}
	return (n_r);
}

t_file	*ft_sort_utime_r(t_file *root)
{
	t_file	*n_r;
	t_file	*n;
	t_file	*cur;

	n_r = NULL;
	while (root)
	{
		n = root;
		root = root->next;
		if (!n_r || n->st->st_atimespec.tv_sec < n_r->st->st_atimespec.tv_sec)
		{
			n->next = n_r;
			n_r = n;
		}
		else
		{
			cur = n_r;
			while (cur->next && n->st->st_atimespec.tv_sec >=
								cur->next->st->st_atimespec.tv_sec)
				cur = cur->next;
			n->next = cur->next;
			cur->next = n;
		}
	}
	return (n_r);
}
