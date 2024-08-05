/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/05 19:09:17 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_see_tilde_ok(char *data);
char		*ft_expand_dollar(char *data, t_env *env);
static int	ft_see_dollar_ok(char *data);
int			ft_see_user(char *str);

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

//TODO do norminette here!
void	ft_view_data(t_token **token, t_env *env)
{
	t_env	*title;
	t_token	*cur;
	char	*str;
	char	*temp;

	cur = *token;
	temp = NULL;
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
	if (ft_strchr(cur->data, '$'))
	{
		str = ft_expand_dollar(cur->data, env);
		free(cur->data);
		cur->data = ft_strdup(str);
		free(str);
	}



	/*
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
	}*/
}

char	*ft_expand_dollar(char *data, t_env *env)
{
	char	**temp = NULL;
	char	**display;
	char	**changer;
	char	*str;
	char	*str_temp;
	t_env	*title;
	int		c;
	int		h;

	c = 0;
	title = ft_get_content(env, "USER");
	str_temp = ft_strchr(data, '$');
	temp = (char **)ft_calloc(words(data, '$' ) + 1, sizeof(char *));
	h = str_temp - data;
	display = temp;
	changer = temp;
	while (data)
	{
		*temp = ft_fine_strdup(data, 0, h - 1);
		c = str_temp - data;
		if (str_temp)
			str_temp = ft_strchr(++str_temp, '$');
		data = data + c;
		if (!str_temp)
			h = ft_strlen(data);
		else
			h = str_temp - data;
		temp++;
	}

	while (*changer != NULL)
	{
		if (ft_see_user(*changer) == SUCCESS && ft_see_dollar_ok(*changer) == SUCCESS)
		{
			free(*changer);
			*changer = ft_strdup(title->content);
		}
		changer++;
	}
	str = ft_array_strjoin(display);
	c = -1;

	while (display[++c] != NULL)
		free(display[c]);
	free(display);
	return (str);
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
	if (ft_isprint(*data))
		return (FAILURE);
	while (*data)
	{
		if (*data == '"')
			return (FAILURE);
		data++;
	}
	return (SUCCESS);
}

static int	ft_see_dollar_ok(char *data)
{
	while (*data)
	{
		if (*data == '\'')
			return (FAILURE);
		data++;
	}
	return (SUCCESS);
}

int	ft_see_user(char *str)
{
	int		c;
	char	*cmp;

	c = 0;
	str++;
	cmp = "USER";
	while (c < 4)
	{
		if (str[c] != cmp[c])
			return (FAILURE);
		c++;
	}
	return (SUCCESS);
}
