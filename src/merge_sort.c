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

t_file	*merge_lists_r(t_file *a, t_file *b)
{
	t_file *merged;

	merged = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (ft_strcmp(a->name, b->name) > 0)
	{
		merged = a;
		merged->next = merge_lists_r(a->next, b);
	}
	else
	{
		merged = b;
		merged->next = merge_lists_r(a, b->next);
	}
	return (merged);
}

t_file	*merge_lists(t_file *a, t_file *b)
{
	t_file *merged;

	merged = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (ft_strcmp(a->name, b->name) < 0)
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
	if (g_r)
		*file = merge_lists_r(a, b);
	else
		*file = merge_lists(a, b);
}
