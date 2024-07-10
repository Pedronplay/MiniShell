/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/10 16:01:38 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **v)
{
	char	*input;
	char	*piped;
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
				piped = ft_pipe_spliter(input);
				token = ft_safe_calloc(words(piped, ' '), sizeof(t_token));
				ft_init_token(token, input);
				ft_print_info(token);
			}
			add_history(input);
			free(input);
		}

	}
	return (0);
}

static int	strlen_pipe(char *str)
{
	int	c;
	int	size;

	c = 0;
	size = ft_strlen(str);
	while (str[c])
	{
		if (str[c] == '|')
			size += 2;
		c++;
	}
	return (c);
}

char	*ft_pipe_spliter(char *str)
{
	size_t		c;
	int			i;
	int			size;
	char		*piped;

	c = 0;
	i = 0;
	size = strlen_pipe(str);
	piped = ft_safe_calloc(size + 1, sizeof(char));
	while (c < ft_strlen(str))
	{
		if (str[c] == '|')
		{
			piped[i++] = ' ';
			piped[i++] = '|';
			piped[i++] = ' ';
		}
		else
			piped[i++] = str[c];
		c++;
	}
	piped[i] = '\0';
	return (piped);
}

void	ft_init_token(t_token *token, char *data)
{
	char	**info;
	char	*piped;
	int		c;
	t_token	*cur;

	c = 0;
	piped = ft_pipe_spliter(data);
	info = ft_split(piped, ' ');
	free(piped);
	while (info[c])
	{
		cur = token + c;
		cur->data = ft_strdup(info[c]);
		ft_data_type(cur);
		if (info[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
	free_args(info);
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
