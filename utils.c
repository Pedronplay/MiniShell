/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:57:32 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/17 10:16:03 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	c;

	c = 0;
	while (s1[c])
	{
		if (s1[c] != s2[c])
			return (FAILURE);
		c++;
	}
	return (SUCCESS);
}

int	ft_check_triples(char *input)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (c < 2 && input[c + 1] != '\0')
	{
		if (input[c] == input[c + 1])
			i++;
		c++;
	}
	if (i == 2)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_space_redirect(char *input)
{
	int		c;

	c = 0;
	if (input[c] == '>' || input[c] == '<')
		c++;
	while (input[c] == ' ')
		c++;
	if (input[c] == '>' || input[c] == '<')
		return (FAILURE);
	return (SUCCESS);
}
