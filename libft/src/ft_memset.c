/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:16:44 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/26 14:16:45 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	if (b == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		((unsigned char*)b)[i] = (unsigned char)c;
	return (b);
}
