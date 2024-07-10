/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:57:32 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 16:58:03 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_type(t_token *token)
{
	if (ft_strcmp(token->data, "echo") == SUCCESS)
		token->type = ECHO;
	else if (ft_strcmp(token->data, "cd") == SUCCESS)
		token->type = CD;
	else if (ft_strcmp(token->data, "pwd") == SUCCESS)
		token->type = PWD;
	else if (ft_strcmp(token->data, "export") == SUCCESS)
		token->type = EXPORT;
	else if (ft_strcmp(token->data, "unset") == SUCCESS)
		token->type = UNSET;
	else if (ft_strcmp(token->data, "env") == SUCCESS)
		token->type = ENV;
	else if (ft_strcmp(token->data, "exit") == SUCCESS)
		token->type = EXIT;
	else if (ft_strcmp(token->data, "flag") == SUCCESS)
		token->type = FLAG;
	else if (ft_strcmp(token->data, "-") == SUCCESS)
		token->type = MATH;
	else if (ft_strcmp(token->data, "|") == SUCCESS)
		token->type = PIPE;
	else
		token->type = WORDS;
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