/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/31 17:15:33 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "minishell.h"
#include <time.h>

void	ft_create_env(char **envp, t_env *env)
{
	int		c;
	int		i;
	t_env	*cur;

	i = ft_arraylen(envp);
	env = ft_calloc(sizeof(t_env), i - 2);
	cur = env;
	ft_println("%d", i);
	c = 0;

	while (c < i - 2)
	{
		cur = env + c;
		cur->title = ft_strdup(envp[c]);
		if (envp[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
	while (env->next != NULL)
	{
		ft_println("%s", env->title);
		env = env->next;
	}
}



//   (void)envp;
int	main(int c, char **v, char **envp)
{
	char	*input;
	char	*clean_input;
	t_token	*token;
	t_env	*env;

	(void)c;
	(void)v;
	env = NULL;
	ft_create_env(envp, env);
	exit(SUCCESS);
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
		ft_data_type(cur, false);
		if (info[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
	ft_data_type(cur, true);
	free_args(info);
}

void	ft_find_expand(t_token **token)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		ft_view_data(cur->data);
		cur = cur->next;
	}
}

void	ft_view_data(char *data)
{
	int	c = 1;

	if (ft_strcmp(data, "~") == true)
		c = 0;

}

