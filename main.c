/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/15 17:05:57 by diogosan         ###   ########.fr       */
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
