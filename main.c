/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/11 18:48:36 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **v, char **envp)
{
	char	*input;
	//char	*piped;
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
			/*else
			{
				piped = ft_pipe_spliter(input);
				token = ft_safe_calloc(words(piped, ' '), sizeof(t_token)); TODO fix this
				ft_init_token(token, input);
				ft_print_info(token);
			}*/
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
