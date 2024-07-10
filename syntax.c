/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:43 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 18:31:31 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_syntax_1place(char *input, int *c)
{
	while (input[*c] == ' ')
		(*c)++;
	if (input[*c] == '|')
		return (FAILURE);
	if (input[*c] == '"')
		return (FAILURE);
	if (input[*c] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_skip_quotes(char *input, int *c)
{
	(*c)++;
	while (input[*c] || input[*c] != '\0')
	{
		if (input[*c] == '"')
		{
			(*c)++;
			return (SUCCESS);
		}
		(*c)++;
	}
	return (FAILURE);
}

static int	ft_syntax_pipes(char *input)
{
	int		c;

	c = 0;
	if (ft_syntax_1place(input, &c) != SUCCESS)
		return (FAILURE);
	else
	{
		while (input[c])
		{
			if (input[c] == '"')
				if (ft_skip_quotes(input, &c) != SUCCESS)
					return (FAILURE);
			if (input[c] == '|')
			{
				if (input[c + 1] == '|' || input[c + 1] == '\0')
					return (FAILURE);
				c++;
				return (ft_syntax_pipes(input + c));
			}
			c++;
		}
	}
	return (SUCCESS);
}



int	ft_validation_input(char *input)
{
	if (ft_syntax_pipes(input) != SUCCESS)
		return (FAILURE);
	//TODO get redirects
	return (SUCCESS);
}
