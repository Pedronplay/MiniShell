/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:30:12 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 12:05:51 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_safe_malloc(int size)
{
	char	*mem;

	mem = malloc(size);
	if (!mem)
		ft_error_exit("malloc error");
	return (mem);
}

void	*ft_safe_calloc(size_t space, size_t type)
{
	char	*mem;

	mem = ft_calloc(space, type);
	if (!mem)
		ft_error_exit("calloc error");
	return (mem);
}
