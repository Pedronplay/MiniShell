/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:57:32 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/16 16:56:42 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_cmd(t_token *token)
{
	if (!token->data)
		return (FAILURE);
	if (ft_strcmp(token->data, "echo") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "cd") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "pwd") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "export") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "unset") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(token->data, "env") == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}


void	ft_data_type(t_token *token)
{
	if (ft_strcmp(token->data, "<") == SUCCESS)
		token->type = R_IN;
	else if (ft_strcmp(token->data, "<<") == SUCCESS)
		token->type = R_IN2;
	else if (ft_strcmp(token->data, ">") == SUCCESS)
		token->type = R_OUT;
	else if (ft_strcmp(token->data, ">>") == SUCCESS)
		token->type = R_OUT2;
	else if (ft_strcmp(token->data, "exit") == SUCCESS)
		token->type = EXIT;
	else if (ft_strcmp(token->data, "flag") == SUCCESS)
		token->type = FLAG;
	else if (ft_strcmp(token->data, "|") == SUCCESS)
		token->type = PIPE;
	else if (ft_check_cmd(token) == SUCCESS)
		token->type = CMD;
	else
		token->type = STR;
}

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
