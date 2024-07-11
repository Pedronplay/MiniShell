/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:43 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/11 16:26:52 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static int	ft_syntax_1place(char *input, int *c, bool redirect)
{
	while (input[*c] == ' ')
		(*c)++;
	if (input[*c] == '|')
		return (FAILURE);
	if (!redirect)
	{
		if (input[*c] == '"')
			return (FAILURE);
		if (input[*c] == '\'')
			return (FAILURE);
	}
	if (input[*c] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_skip_quotes(char *input, int *c, char i)
{
	(*c)++;
	while (input[*c] || input[*c] != '\0')
	{
		if (input[*c] == i)
			return (SUCCESS);
		(*c)++;
	}
	return (FAILURE);
}

static int	ft_syntax_pipes(char *input)
{
	int		c;

	c = 0;
	if (ft_syntax_1place(input, &c, false) != SUCCESS)
		return (FAILURE);
	else
	{
		while (input[c])
		{
			if (input[c] == '"' || input[c] == '\'')
				if (ft_skip_quotes(input, &c, input[c]) != SUCCESS)
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

static int	ft_redirect_type(char *input)
{
	bool	left;
	bool	right;
	int		c;

	left = false;
	right = false;
	c = 0;
	while (c < 2)
	{
		if (input[c] == '<')
			left = true;
		if (input[c] == '>')
			right = true;
		c++;
	}
	if (input[c] == '<' || input[c] == '>')
		return (FAILURE);
	if (left && right)
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_syntax_redirects(char *input)
{
	int		c;

	c = 0;
	if (ft_syntax_1place(input, &c, true) != SUCCESS)
		return (FAILURE);
	else
	{
		while (input[c])
		{
			if (input[c] == '"' || input[c] == '\'')
				if (ft_skip_quotes(input, &c, input[c]) != SUCCESS)
					return (FAILURE);
			if (input[c] == '>' || input[c] == '<')
			{
				if (ft_redirect_type(input + c) != SUCCESS)
					return (FAILURE);
				c++;
				if (input[c] == '|')
					return (FAILURE);
				return (ft_syntax_redirects(input + c));
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
	if (ft_syntax_redirects(input) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
