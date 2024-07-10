/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 13:57:18 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **v)
{
	char	*input;
	t_token	*token;

	token = NULL;

	(void)c;
	(void)v;

	while (1)
	{
		input = readline("MiniHell$> ");
		if (input == NULL || *input == '+')
			break ;
		if (*input)
		{
			if (ft_syntax_checker(input) == FAILURE)
				ft_println("Wrong Syntax");
			else
			{
				token = ft_safe_calloc(words(input, ' '), sizeof(t_token));
				ft_init_token(token, input);
				ft_print_info(token);
			}
			add_history(input);
			free(input);
		}

	}
	return (0);
}

void	ft_init_token(t_token *token, char *data)
{
	char	**info;
	int		c;
	t_token	*cur;

	c = 0;
	info = ft_split(data, ' ');
	while (info[c])
	{
		cur = token + c;
		cur->data = info[c];
		ft_data_type(cur);
		if (info[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
}

void	ft_data_type(t_token *token)
{
	if (ft_strcmp(token->data, "cd") == SUCCESS)
		token->type = CD;
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

int	ft_syntax_checker(char *input)
{
	int		c;

	c = 0;
	while (input[c] == ' ')
		c++;
	if (input[c] == '|')
		return (FAILURE);
	else
	{
		while (input[c])
		{
			if (input[c] == '|')
			{
				if (input[c + 1] == '|' || input[c + 1] == '\0'
					|| input[c] == '\0')
					return (FAILURE);
				c++;
				return (ft_syntax_checker(input + c));
			}
			c++;
		}
	}
	return (SUCCESS);
}
