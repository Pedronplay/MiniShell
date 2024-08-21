/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:06:43 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/21 21:30:13 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_send_to_execve(t_token *token, t_env *env);

void	ft_execute_in(t_token *token, t_env *env)
{
	int	forked;

	forked = 1;
	// get FORKED MINIHELL    FIRST  -> prepare args and envs  <-
	// Builtins that dont kill the program and affect it: Only if pipes 
	//				CD, export, unset
	// builtins that have to kill that version of the program
	//				env, pwd, echo
	if (ft_strcmp(token->data, "cd") || ft_strcmp(token->data, "export")
	|| ft_strcmp(token->data, "unset"))
			ft_built_in(token, env);
	else
	{
		forked = fork();
		while (wait(NULL) > 0);
	}
	if (forked == 0 && ft_built_in(token, env) == 1)
		ft_send_to_execve(token, env);
	if (forked == 0)
	{
		free_tokens(token);
		ft_free_env(env);
		exit(0);
	}
}

int		ft_built_in(t_token *token, t_env *env)
{
	if (!token)
		return 0;
	else if (ft_strcmp(token->data, "env") == SUCCESS)
		ft_env(env, token);
	else if (ft_strcmp(token->data, "pwd") == SUCCESS)
		ft_pwd(token);
	else if (ft_strcmp(token->data, "echo") == SUCCESS)
		ft_echo(token);
	else if (ft_strcmp(token->data, "cd") == SUCCESS)
		ft_cd(token); // 
	else if (ft_strcmp(token->data, "export") == SUCCESS)
		ft_printf("this will export soon\n"); // 6 
	else if (ft_strcmp(token->data, "unset") == SUCCESS)
		ft_printf("this will unset soon\n"); // 5
	else
		return 1;
	return 0;
}
char	**ft_make_env_arr(t_env *env)
{
	t_env	*temp;
	char	**envs;
	char	*title;
	int		i;

	temp = env;
	i = 0;
	if (!env)
		return NULL;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	envs = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = env;
	while (temp)
	{
		title = ft_strjoin(temp->title, "=");
		envs[i++] = ft_strjoin(title, temp->content);
		free(title);
		temp = temp->next;
	}
	return (envs);
}

char	**ft_make_arg_arr(t_token *token)
{
	t_token	*temp;
	char 	**args;
	int		i;

	i = 0;
	if (!token)
		return NULL;
	temp = token;
	while(temp)
	{
		temp = temp->next;
		i++;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = token;
	while(temp)
	{
		args[i] = temp->data;
		temp = temp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	*ft_get_env(t_env *env, char *str)
{
	while (env->next != NULL)
	{
		if (!env->title)
			break ;
		if (ft_strcmp(str, env->title) != 1)
			env = env->next;
		else
			break;
	}
	if (env->title && ft_strcmp(str, env->title) == 1)
		return env->content;
	if (env->next && ft_strcmp(str, env->next->title))
		return env->next->title;
	return NULL;
}

char	*ft_path_to_executable(char **paths, char *command)
{
	int	i;
	DIR		*dir;
	struct dirent *entry;
	
	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0)
		{
			if (paths[i] == NULL)
				return NULL;
			dir = opendir(paths[i]);
			while ((entry = readdir(dir)) != NULL)
			{
				if (strcmp(entry->d_name, command) == 0)
					return (paths[i]);
			}
			closedir(dir);
		}
		i++;
	}
	return (NULL);
}

void	ft_free_shit_up(char **evs, char **args, char *found, char *pndd, char **pth)
{	
	free_args(evs);
	free(args);
	free(found);
	free(pndd);
	free_args(pth);
}

char	*ft_path(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	return (buffer);
}

void	ft_send_to_execve(t_token *token, t_env *env)
{
	char	**args_arr;
	char	**env_arr;
	char	**paths;
	char	*found;
	char	*apended;

	paths = NULL;
	env_arr = ft_make_env_arr(env);
	args_arr = ft_make_arg_arr(token);
	if (ft_get_env(env, "PATH") != NULL)
	{
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		found = ft_path_to_executable(paths, token->data); 
	}
	else // At this point i know i didnt find the program in the PATHS of the env so i use pwd
		found = ft_path();
	if (!ft_strnstr(token->data, "./", ft_strlen(token->data))) //ft_in_there(token->data, "./") == 0)
	{
		found = ft_strjoin(found, "/");
		apended = ft_strjoin(found, token->data);
	}
	else
		apended = token->data;
	if (execve(apended, args_arr, env_arr) == -1)// o path leva o programa o path e lido pelas envs
		ft_printf_err("command '%s' not found\n", token->data);
	ft_free_shit_up(env_arr, args_arr, found, apended, paths);
}
/*
void	ft_send_to_execve(t_token *token, t_env *env)
{
	char	**args_arr;
	char	**env_arr;
	char	**paths;
	char	*found;
	char	*apended;

	//paths = NULL;
	env_arr = ft_make_env_arr(env);
	args_arr = ft_make_arg_arr(token);
	if (ft_get_env(env, "PATH") != NULL)
	{
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		found = ft_path_to_executable(paths, token->data); 
	}
	else // At this point i know i didnt find the program in the PATHS of the env so i use pwd
		found = ft_path();
	if (ft_in_there(token->data, "./") == 0)
	{
		found = ft_strjoin(found, "/");
		apended = ft_strjoin(found, token->data);
	}
	else
		apended = token->data;
	if (execve(apended, args_arr, env_arr) == -1)// o path leva o programa o path e lido pelas envs
		ft_printf_err("command '%s' not found\n", token->data);
	ft_free_shit_up(env_arr, args_arr, found, apended, paths);
}

int	ft_in_there(char *hay, char *needle)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;
	while (hay[i] != '\0')
	{
		j = 0;
		while (hay[i] && hay[i] == needle[j])
		{
			if(needle[j + 1] == '\0')
				return (1);
			j++;
			i++;
		}
		i++;
	}
	return (0);
}*/