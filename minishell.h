/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:37:41 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/05 15:37:40 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include "libraries/printf/ft_printf.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_exit
{
	FAILURE,
	SUCCESS,
}	t_exit;

/*
	comands:
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
*/

typedef struct s_env
{
	char			*title;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	CMD,
	BUILT_IN,
	EXIT,
	STR,
	FLAG,
	PIPE,
	R_IN,
	R_IN2,
	R_OUT,
	R_OUT2,
}	t_type;

typedef struct s_token
{
	char				*data;
	t_type				type;
	struct s_token		*next;
}	t_token;

//------------tester.c----------------
void	ft_print_info(t_token *token);

//------------main.c----------------
void	ft_init_token(t_token *token, char *data);

//------------type_check.c----------------
void	ft_data_type(t_token *token, bool reset);


//------------expand.c----------------
void	ft_find_expand(t_token **token, t_env *env);
void	ft_view_data(t_token **token, t_env *env);
t_env	*ft_get_content(t_env *env, char *title);

//------------token_utils.c----------------
int		ft_clean_size(char *str);
char	*ft_input_spliter(char *str);

//------------syntax.c----------------
int		ft_skip_quotes(char *input, int *c, char i);
int		ft_syntax_redirects(char *input);
int		ft_syntax_pipes(char *input);

//------------ft_quotes_split.c-------
char	**ft_quotes_split(char *s, char c);
int		words_quotes(char *s, char c);

//------------free_funcs.c -------
void	free_tokens(t_token *stack);
void	ft_free_env(t_env *env);

//------------syntax2.c -------
int		ft_validation_input(char *input);

//------------utils.c -------
int		ft_strcmp(const char *s1, const char *s2);
int		ft_check_triples(char *input);
int		ft_space_redirect(char *input);
char	*ft_strcat(char *str1, char *str2);
char	*ft_array_strjoin(char **array);

//------------utils2.c -------
void	ft_space_skiper(char *str, int *c);
void	ft_reset_int(int *c, int *i);
void	ft_count_helper(char *str, int *c, int *size);
void	ft_skip_quotes_w(char *input, char **dst, int *c, int *i);
void	ft_space_helper(char *str, char **dst, int *c, int *i);

#endif
