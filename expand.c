/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/12 12:45:20 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_dollar(char *data, t_env *env);
int		ft_see_expand(char *str);
int		ft_see_inst_char(char *str, char c);

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
	if (str)
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
	if (str)
	{
		if (!*++str)
			return ;
		else if (ft_isdigit(*str) == SUCCESS || *str == '?')
		{
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
		else
		{
			str = NULL;
			str = ft_expand_dollar(cur->data, env);
			//ft_println("%s", str);
			//free(str);
			free(cur->data);
			cur->data = ft_strdup(str);
			free(str);
		}
	}
}

char	*ft_expand_dollar(char *data, t_env *env)
{
	char	**temp;
	t_env	*title;
	char	*str;
	int		c;
	int		d;
	int		p;

	p = 0;
	temp = NULL;
	c = 0;
	d = 0;
	title = ft_get_content(env, "USER");
	temp = (char **)ft_calloc(ft_see_inst_char(data, '$') + 1, sizeof(char *));
	while (data[c])
	{
		if (data[c] == '\"' || data[c] == '\'')
		{
			d = c;
			ft_skip_quotes(data, &c, data[c]);
			temp[p++] = ft_fine_strdup(data, d, c);
			c++;
			if (data[c] == '\0')
				break ;
		}
		else if (data[c] == '$')
		{
			d = c;
			c++;
			while (data[c] != '$' && data[c] != '\"' && data[c] != '\'' && data[c] != '\0')
				c++;
			temp[p++] = ft_fine_strdup(data, d, c - 1);
		}
		else
			c++;

	}
	c = 0;
	while (temp[c])
	{
		if (ft_see_expand(temp[c]))
		{
			free(temp[c]);
			temp[c] = ft_strdup(title->content);
		}
		c++;
	}
	str = ft_array_strjoin(temp);
	char **cur = temp;
	while (*temp)
		free(*temp++);
	free(cur);

	return (str);
}

int	ft_see_inst_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (*str != c)
		i++;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
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

int	ft_see_expand(char *str)
{
	int		c;
	char	*cmp;

	if (*str == '\"')
		str++;
	c = 0;
	cmp = "$USER";
	while (c <= 4)
	{
		if (str[c] != cmp[c])
			return (FAILURE);
		c++;
	}
	return (SUCCESS);
}
