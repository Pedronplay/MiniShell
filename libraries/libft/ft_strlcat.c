/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:35:45 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/20 14:09:47 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	c;
	size_t	c2;
	size_t	i;

	c = 0;
	c2 = 0;
	while (dest[c] && c < size)
	{
		c++;
		c2++;
	}
	if (c2 == size)
		return (c2 + ft_strlen(src));
	i = 0;
	while (src[i])
	{
		if (i < size - 1 - c2)
		{
			dest[c] = src[i];
			c++;
		}
		i++;
	}
	dest[c] = '\0';
	return (c2 + i);
}
