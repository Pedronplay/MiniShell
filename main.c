/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/15 16:55:15 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "libraries/printf/ft_printf.h"
#include "minishell.h"

int	main(int c, char **v, char **envp)
{
	char	*input;
	t_token	*token;

	token = NULL;

	(void)c;
	(void)v;
	(void)envp;

	while (1)
	{
		input = readline("MiniHell$> ");
		if (input == NULL || *input == '+')
			break ;
		if (*input)
		{
			if (ft_validation_input(input) == FAILURE)
				ft_println("Wrong Syntax");

			else
			{
				//ft_println("%s", input);
				ft_println("%d",ft_clean_size(input));
				ft_println("%s",ft_input_spliter(input));
				//token = ft_safe_calloc(words(piped, ' '), sizeof(t_token)); TODO fix this
				//ft_init_token(token, input);
				//ft_print_info(token);
			}
			add_history(input);
			free(input);
		}

	}
	return (0);
}


static void	ft_count_helper(char *str, int *c, int *size)
{
	if (str[*c - 1] == ' ' && str[*c + 1] == ' ')
		return ;
	if (str[*c - 1] != ' ')
		(*size)++;
	if (str[*c + 1] != ' ')
		(*size)++;
}

static void	ft_see_space(char *str, int *c, int *size)
{
	if (str[*c] == '>' || str[*c] == '<')
	{
		if (str[*c + 1] == '>' || str[*c + 1] == '<')
		{
			(*c)++;
			(*size) += 2;
			if (str[*c + 1] != ' ')
				(*size)++;
		}
		else
		{
			if (str[*c - 1] == ' ' && str[*c + 1] == ' ')
				return ;
			if (str[*c - 1] != ' ')
				(*size)++;
			if (str[*c + 1] != ' ')
				(*size)++;
		}
		return ;
	}
	else
	{
		ft_count_helper(str, c, size);
		return ;
	}
}

static void	ft_space_helper(char *str, char **dst, int *c, int *i)
{
	if (str[*c - 1] == ' ' && str[*c + 1] == ' ')
	{
		(*dst)[*i] = str[*c];
		return ;
	}
	if (str[*c - 1] != ' ')
		(*dst)[(*i)++] = ' ';
	(*dst)[*i] = str[*c];
	if (str[*c + 1] != ' ')
		(*dst)[++(*i)] = ' ';
}

static void	ft_set_space(char *str, char **dst, int *c, int *i)
{
	if (str[*c] == '>' || str[*c] == '<')
	{
		if (str[*c + 1] == '>' || str[*c + 1] == '<')
		{
			if (str[*c - 1] != ' ')
				(*dst)[(*i)++] = ' ';
			(*dst)[(*i)++] = str[(*c)++];
			(*dst)[*i] = str[*c];
			if (str[*c + 1] != ' ')
				(*dst)[++(*i)] = ' ';
			return ;
		}
		else
		{
			ft_space_helper(str, dst, c, i); // Puts the spaces ex a<a - > a < a
			return ;
		}
	}
	else
		ft_space_helper(str, dst, c, i);// same as above
	return ;
}

int	ft_clean_size(char *str)
{
	int	c;
	int	size;

	c = 0;
	size = 0;
	ft_space_skiper(str, &c);
	while (str[c] != '\0')
	{
		if (str[c] != ' ')
		{
			while (str[c] != ' ' && str[c] != '\0')
			{
				if ((str[c] == '|' || str[c] == '<' || str[c] == '>'))
					ft_see_space(str, &c, &size);
				c++;
				size++;
			}
		}
		else
		{
			ft_space_skiper(str, &c);
			if (str[c] != '\0')
				size++;
		}
	}
	return (size);
}

char	*ft_input_spliter(char *str)
{
	int		size;
	char	*clean_input;
	int		c;
	int		i;

	c = 0;
	i = 0;
	size = ft_clean_size(str);
	clean_input = ft_safe_calloc(size + 1, sizeof(char));
	ft_space_skiper(str, &c);
	while (str[c] != '\0')
	{
		if (str[c] != ' ')
		{
			while (str[c] != ' ' && str[c] != '\0')
			{
				if (str[c] == '"' || str[c] == '\'')
					ft_skip_quotes_w(str, &clean_input, &c, &i);
				if ((str[c] == '|' || str[c] == '<' || str[c] == '>'))
					ft_set_space(str, &clean_input, &c, &i);
				else
				{
					if (str[c] != ' ' && str[c] != '\0')
						clean_input[i] = str[c];
				}
				c++;
				i++;
			}
		}
		else
		{
			clean_input[i++] = str[c++];
			ft_space_skiper(str, &c);
		}
	}
	clean_input[i] = '\0';
	return (clean_input);
}


void	ft_init_token(t_token *token, char *data)
{
	char	**info;
	char	*clean;
	int		c;
	t_token	*cur;

	c = 0;
	clean = ft_input_spliter(data);
	info = ft_split(clean, ' ');
	free(clean);
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
