/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/16 16:55:29 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int c, char **v, char **envp (void)c; (void)v; (void)envp;
int	main(void)
{
	char	*input;
	char	*clean_input;
	t_token	*token;

	token = NULL;
	while (1)
	{
		input = readline("MiniHell$> ");
		if (input == NULL || ft_strcmp(input, "exit") == SUCCESS)
		{
			free(input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (ft_validation_input(input) == FAILURE)
				ft_println("Wrong Syntax");
			else
			{
				clean_input = ft_input_spliter(input);
				token = ft_calloc(sizeof(t_token),
						words_quotes(clean_input, ' '));
				free(clean_input);
				ft_init_token(token, input);
				ft_print_info(token);
				free_tokens(token);
			}
			free(input);
		}
	}
	return (0);
}

void	ft_init_token(t_token *token, char *data) // data
{
	char	**info;
	char	*clean_input;
	int		c;
	t_token	*cur;

	c = 0;
	clean_input = ft_input_spliter(data);
	info = ft_quotes_split(clean_input, ' ');
	free(clean_input);
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

