/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:48 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/05 18:28:22 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *src)
{
	int		c;
	char	*dest;

	dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!dest)
		return (0);
	c = 0;
	while (src[c])
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = '\0';
	return (dest);
}

/*
	Returns the a duple of the string with end on the end position
	Example -> (user=myfriend, 0, 3) = user
*/
char	*ft_fine_strdup(char const *src, int start, int end)
{
	int		c;
	char	*dest;

	dest = (char *)ft_calloc((end - start) + 2, sizeof(char));
	if (!dest)
		return (0);
	c = 0;
	while (start <= end)
	{
		dest[c] = src[start];
		start++;
		c++;
	}
	dest[c] = '\0';
	return (dest);
}
