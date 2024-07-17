/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:48 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/17 12:00:29 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == 0)
		return ((char *)str);
	return (NULL);
}

int	ft_strchr_bool(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return (0);
		str++;
	}
	return (1);
}
/*
int	main()
{
	char	*ptr;
	char	tweet[] = "ola friend";
	
	ptr = ft_strchr(tweet, 'f');
	
	printf("%s", ptr);
}
*/
