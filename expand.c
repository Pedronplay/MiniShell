/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/01 17:06:50 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_see_tilde_ok(char *data);
static int	ft_see_dollar_ok(char *data);

void	ft_find_expand(t_token **token, t_env *env)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		ft_view_data(&cur, env);
		cur = cur->next;
	}
}

void	ft_view_data(t_token **token, t_env *env)
{
	t_env	*title;
	t_token	*cur;
	char	*str;
	char	*temp;

	cur = *token;

	str = ft_strchr(cur->data, '~');
	if (str && ft_see_tilde_ok(str) == SUCCESS)
	{
		title = ft_get_content(env, "HOME");
		if (!*++str)
		{
			free(cur->data);
			cur->data = ft_strdup(title->content);
		}
		else if (*str == '/')
		{

			temp = ft_strcat(title->content, str);
			free(cur->data);
			cur->data = ft_strdup(temp);
			free(temp);
		}
	}
	str = ft_strchr(cur->data, '$');
	if (str && (ft_strcmp(cur->data, "\"$USER\"") == SUCCESS || ft_strcmp(cur->data, "$USER") == SUCCESS) && ft_see_dollar_ok(str) == SUCCESS)
	{
		title = ft_get_content(env, "USER");
		free(cur->data);
		cur->data = ft_strdup(title->content);
	}
	else if (str && (ft_isdigit(str[1]) == SUCCESS || str[1] == '?'))
	{
		str++;
		if (*str == '0')
		{
			free(cur->data);
			cur->data = ft_strdup("minishell");
		}	
		else if (*str > '0' && *str <= '9')
		{
			free(cur->data);
			cur->data = ft_strdup("\n");
		}
		else
		{
			free(cur->data);
			cur->data = ft_strdup("Error code bro!");
		}
	}
}

t_env	*ft_get_content(t_env *env, char *title)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->title, title) == SUCCESS)
			return (cur);
		cur = cur->next;
	}
	return (env);
}


static int	ft_see_tilde_ok(char *data)
{
	--data;
	if (ft_isalnum(*data) == SUCCESS)
		return (FAILURE);
	while(*data)
	{
		if (*data == '"')
			return (FAILURE);
		data++;
	}
	return (SUCCESS);
}

static int	ft_see_dollar_ok(char *data)
{
	--data;
	if (ft_isalnum(*data++) == SUCCESS)
		return (FAILURE);
	while(*data)
	{
		if (*data == '\'')
			return (FAILURE);
		data++;
	}
	return (SUCCESS);
}