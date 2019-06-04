/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:10:27 by omiroshn          #+#    #+#             */
/*   Updated: 2019/05/18 18:10:28 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// t_file	*merge_lists_t(t_file *a, t_file *b)
// {
// 	t_file *merged;

// 	merged = NULL;
// 	if (a == NULL)
// 		return b;
// 	else if (b == NULL)
// 		return a;
// 	if ((a->st->st_mtimespec.tv_sec - b->st->st_mtimespec.tv_sec) > 0)
// 	{
// 		merged = a;
// 		merged->next = merge_lists_t(a->next, b);
// 	}
// 	else
// 	{
// 		merged = b;
// 		merged->next = merge_lists_t(a, b->next);
// 	}
// 	return (merged);
// }

// t_file *ft_sort_mtime(t_file *head)
// {
// 	t_file *current;
// 	t_file *node;
// 	t_file *next;

// 	next = NULL;
// 	while (head)
// 	{
// 		node = head;
// 		head = head->next;
// 		if (!next || node->st->st_mtimespec.tv_sec < next->st->st_mtimespec.tv_sec)
// 		{
// 			node->next = next;
// 			next = node;
// 		}
// 		else
// 		{
// 			current = next;
// 			while (current->next && node->st->st_mtimespec.tv_sec >= current->next->st->st_mtimespec.tv_sec)
// 				current = current->next;
// 			node->next = current->next;
// 			current->next = node;
// 		}
// 	}
// 	return (next);
// }

static t_file	*ft_sort_mtime(t_file *root)
{
	t_file	*n_r;
	t_file	*node;
	t_file	*cur;

	n_r = NULL;
	while (root != NULL)
	{
		node = root;
		root = root->next;
		if (!n_r || node->st->st_mtimespec.tv_sec < n_r->st->st_mtimespec.tv_sec)
		{
			node->next = n_r;
			n_r = node;
		}
		else
		{
			cur = n_r;
			while (cur->next && node->st->st_mtimespec.tv_sec >= cur->next->st->st_mtimespec.tv_sec)
				cur = cur->next;
			node->next = cur->next;
			cur->next = node;
		}
	}
	return (n_r);
}

t_file	*merge_lists(t_file *a, t_file *b)
{
	t_file *merged;

	merged = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (g_r ? ft_strcmp(a->name, b->name) > 0 :
			ft_strcmp(a->name, b->name) < 0)
	{
		merged = a;
		merged->next = merge_lists(a->next, b);
	}
	else
	{
		merged = b;
		merged->next = merge_lists(a, b->next);
	}
	return (merged);
}

void	partition(t_file *src, t_file **a, t_file **b)
{
	t_file *fast;
	t_file *slow;

	slow = src;
	fast = src->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = src;
	*b = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_file **file)
{
	t_file *head;
	t_file *a;
	t_file *b;

	head = *file;
	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*file = merge_lists(a, b);
	if (g_t)
		*file = ft_sort_mtime(*file);
}
