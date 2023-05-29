/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:23:15 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/28 07:01:11 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_exit_code;

int	length_of_dollar_sign(char *str)
{
	t_counter	count;

	if (!str || !str[0] || str[0] != '$')
		return (0);
	count.i = 1;
	while (str[count.i] && (ft_isalnum(str[count.i]) == 1 || str[count.i] == '_'))
		count.i++;
	return (count.i - 1);
}

int	get_length_of_env(char *str)
{
	t_counter	count;
	char		*env_value;
	char		*env_key;

	if (!str || !str[0] || str[0] != '$' || !str[1])
		return (0);
	count.i = 1;
	count.j = length_of_dollar_sign(str);
	env_key = malloc(sizeof(char) * count.j);
	while (str[count.i] && (ft_isalnum(str[count.i]) != 0 || str[count.i] == '_'))
	{
		env_key[count.i - 1] = str[count.i];
		count.i++;
	}
	env_key[count.i - 1] = '\0';
	env_value = getenv(env_key + 1);
	count.counter = ft_strlen(env_value);
	if (env_key)
		free(env_key);
	if (env_value)
		free(env_value);
	return (count.counter);
}

int	is_expandable(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (FALSE);
	count.i = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\"')
			{
				if (str[count.i] == '$' && str[count.i + 1] && (ft_isalnum(str[count.i + 1]) == 1 || str[count.i + 1] == '_'))
					return (TRUE);
				count.i++;
			}
			if (str[count.i] && str[count.i] == '\"')
				count.i++;
			continue ;
		}
		else if (str[count.i] == '\'')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\'')
				count.i++;
			count.i++;
			continue ;
		}
		else if (str[count.i] == '$' && str[count.i + 1] && (ft_isalnum(str[count.i + 1]) == 1 || str[count.i + 1] == '_'))
			return (TRUE);
		else
			count.i++;
	}
	return (FALSE);
}
// printf("%s is expandable and isalnum = %i\n", str, ft_isalnum(str[count.i + 1])),
// printf("%s is not expandable\n", str),

int	number_of_expansions(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\'')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\'')
				count.i++;
			count.i++;
		}
		else if (str[count.i] == '$')
		{
			count.counter++;
			count.i++;
			while (str[count.i] && (ft_isalnum(str[count.i]) == 1 || str[count.i] == '_'))
				count.i++;
		}
		else
			count.i++;
	}
	return (count.counter);
}

int	is_exit_code_expansion(char *str)
{
	t_counter	count;

	if (!str)
		return (FALSE);
	count.i = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\"')
			{
				if (str[count.i] == '$' && str[count.i + 1] && str[count.i + 1] == '?')
					return (TRUE);
				count.i++;
			}
			if (str[count.i] && str[count.i] == '\"')
				count.i++;
		}
		else if (str[count.i] == '\'')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\'')
				count.i++;
			if (str[count.i] && str[count.i] == '\'')
				count.i++;
		}
		else
		{
			if (str[count.i] == '$' && str[count.i + 1] && str[count.i + 1] == '?')
				return (TRUE);
			count.i++;
		}
	}
	return (FALSE);
}

char	*expand_token(char *old_token)
{
	t_counter	count;
	char		*new_token;
	char		*env_value;
	char		*dollar_sign;

	if (!old_token)
		return (NULL);
	count.i = 0;
	count.trigger = 0;
	new_token = NULL;
	// get dollar_sign
	while (old_token[count.i] && count.trigger == 0)
	{
		if (old_token[count.i] == '\"')
		{
			count.i++;
			while (old_token[count.i] && old_token[count.i] != '\"' && count.trigger == 0)
			{
				if (old_token[count.i] == '$' && old_token[count.i + 1] && old_token[count.i + 1] != '?')
				{
					count.y = 0;
					count.z = length_of_dollar_sign(old_token + count.i);
					dollar_sign = malloc(sizeof(char) * (count.z) + 1);
					count.i++;
					while (old_token[count.i] && (ft_isalnum(old_token[count.i]) || old_token[count.i] == '_'))
						dollar_sign[count.y++] = old_token[count.i++];
					dollar_sign[count.y] = '\0';
					count.trigger = 1;
				}
				else
					count.i++;
			}
			if (old_token[count.i] && old_token[count.i] == '\"')
				count.i++;
		}
		else if (old_token[count.i] == '\'')
		{
			count.i++;
			while (old_token[count.i] && old_token[count.i] != '\'')
				count.i++;
			if (old_token[count.i] && old_token[count.i] == '\'')
				count.i++;
		}
		else if (old_token[count.i] == '$' && old_token[count.i + 1] && old_token[count.i + 1] != '?')
		{
			count.y = 0;
			count.z = length_of_dollar_sign(old_token + count.i);
			dollar_sign = malloc(sizeof(char) * (count.z) + 1);
			count.i++;
			while (old_token[count.i] && (ft_isalnum(old_token[count.i]) || old_token[count.i] == '_'))
				dollar_sign[count.y++] = old_token[count.i++];
			dollar_sign[count.y] = '\0';
			count.trigger = 1;
		}
		else
			count.i++;
	}
	// expand dollar sign
	env_value = getenv(dollar_sign);
	count.i = 0;
	count.j = 0;
	count.k = 0;
	if (env_value)
	{
		count.m = (ft_strlen(env_value) + ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1));
		new_token = malloc(sizeof(char) * (ft_strlen(env_value) + ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1)) + 1);
	}
	else
	{
		count.m = (ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1));
		new_token = malloc(sizeof(char) * (ft_strlen(old_token) - (ft_strlen(dollar_sign) - 1)) + 1);
	}
	while (old_token[count.i])
	{
		if (old_token[count.i] == '\"')
		{
			new_token[count.j++] = old_token[count.i++];
			while (old_token[count.i] && old_token[count.i] != '\"')
			{
				if (old_token[count.i] == '$' && old_token[count.i + 1] && old_token[count.i + 1] != '?')
				{
					if (env_value && env_value[0])
						while (count.j < count.m && env_value[count.k])
							new_token[count.j++] = env_value[count.k++];
					count.i += length_of_dollar_sign(old_token + count.i) + 1;
					while (count.j < count.m && old_token[count.i])
						new_token[count.j++] = old_token[count.i++];
					new_token[count.j] = '\0';
					return (new_token);
				}
				else
					new_token[count.j++] = old_token[count.i++];
			}
			if (count.j < count.m && old_token[count.i] && old_token[count.i] == '\"')
				new_token[count.j++] = old_token[count.i++];
		}
		else if (old_token[count.i] == '\'')
		{
			count.i++;
			while (old_token[count.i] && old_token[count.i] != '\'')
				count.i++;
			if (old_token[count.i] && old_token[count.i] == '\'')
				count.i++;
		}
		else if (old_token[count.i] == '$' && old_token[count.i + 1] && old_token[count.i + 1] != '?')
		{
			if (env_value && env_value[0])
				while (count.j < count.m && env_value[count.k])
					new_token[count.j++] = env_value[count.k++];
			count.i += length_of_dollar_sign(old_token + count.i) + 1;
			while (count.j < count.m && old_token[count.i])
				new_token[count.j++] = old_token[count.i++];
			new_token[count.j] = '\0';
			return (new_token);
		}
		else
			new_token[count.j++] = old_token[count.i++];
	}
	new_token[count.j] = '\0';
	free(old_token);
	return (new_token);
}
					// printf("new token = %s\n", new_token);
			// printf("new token = %s\n", new_token);
	// printf("Dollar sign = %s\n", dollar_sign);
	// printf("env_value = %s\n", env_value);
		// printf("length of new_token = %li\n", (ft_strlen(env_value) + ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1)));
		// printf("length of new_token = %li\n", (ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1)));

int	exit_expansion_token_size(t_shell_s *minishell, char *str)
{
	t_counter	count;

	(void)minishell;
	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			count.i++;
			count.counter++;
			while (str[count.i] && str[count.i] != '\"')
			{
				if (str[count.i] == '$' && str[count.i + 1] && str[count.i + 1] == '?')
				{
					count.counter += ft_strlen(ft_itoa(g_exit_code));
					count.i += 2;
				}
				else
				{
					count.i++;
					count.counter++;
				}
			}
			if (str[count.i] && str[count.i] == '\"')
			{
				count.i++;
				count.counter++;
			}
		}
		else if (str[count.i] == '\'')
		{
			count.i++;
			count.counter++;
			while (str[count.i] && str[count.i] != '\'')
			{
				count.i++;
				count.counter++;
			}
			if (str[count.i] && str[count.i] == '\'')
			{
				count.i++;
				count.counter++;
			}
		}
		else
		{
			if (str[count.i] == '$' && str[count.i + 1] && str[count.i + 1] == '?')
			{
				count.counter += ft_strlen(ft_itoa(g_exit_code));
				count.i += 2;
			}
			else
			{
				count.i++;
				count.counter++;
			}
		}
	}
	return (count.counter);
}

char	*expand_exit_code_token(t_shell_s *minishell, char *str)
{
	t_counter	count;
	char		*new_str;
	char		*exit_code;

	if (!str || !str[0])
		return (NULL);
	count.i = 0;
	count.j = 0;
	// printf("Exit code in function = %i\n", g_exit_code);
	exit_code = ft_itoa(g_exit_code);
	new_str = malloc(sizeof(char) * (exit_expansion_token_size(minishell, str)) + 1);
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			new_str[count.j++] = str[count.i++];
			while (str[count.i] && str[count.i] != '\"')
			{
				if (str[count.i] == '$' && str[count.i + 1] && str[count.i + 1] == '?')
				{
					count.k = 0;
					while (exit_code[count.k])
						new_str[count.j++] = exit_code[count.k++];
					count.i += 2;
				}
				else
					new_str[count.j++] = str[count.i++];
			}
			if (str[count.i] && str[count.i] == '\"')
				new_str[count.j++] = str[count.i++];
		}
		else if (str[count.i] == '\'')
		{
			new_str[count.j++] = str[count.i++];
			while (str[count.i] && str[count.i] != '\'')
				new_str[count.j++] = str[count.i++];
			if (str[count.i] && str[count.i] == '\'')
				new_str[count.j++] = str[count.i++];
		}
		else
		{
			if (str[count.i] == '$' && str[count.i + 1] && str[count.i + 1] == '?')
			{
				count.k = 0;
				while (exit_code[count.k])
					new_str[count.j++] = exit_code[count.k++];
				count.i += 2;
			}
			else
				new_str[count.j++] = str[count.i++];
		}
	}
	new_str[count.j] = '\0';
	return (new_str);
}

t_shell_s	*expand_env_variables(t_shell_s *minishell)
{
	t_counter	count;
	char		*old_token;

	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
		return (NULL);
	count.i = 0;
	count.j = 0;
	while (minishell->lexer->tokens[count.i])
	{
		if (is_expandable(minishell->lexer->raw_tokens[count.i]) == TRUE)
		{
			old_token = ft_strdup(minishell->lexer->raw_tokens[count.i]);
			free(minishell->lexer->raw_tokens[count.i]);
			minishell->lexer->raw_tokens[count.i] = expand_token(old_token);
			free(old_token);
		}
		else if (is_exit_code_expansion(minishell->lexer->raw_tokens[count.i]) == TRUE)
		{
			old_token = ft_strdup(minishell->lexer->raw_tokens[count.i]);
			free(minishell->lexer->raw_tokens[count.i]);
			minishell->lexer->raw_tokens[count.i] = expand_exit_code_token(minishell, old_token);
			free(old_token);
		}
		else
			count.i++;
	}
	return (minishell);
}
			// printf("%s\n", minishell->lexer->raw_tokens[count.i]);

int	token_size2(char *str)
{
	t_counter	count;

	if (!str)
		return (0);
	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\"')
			{
				count.counter++;
				count.i++;
			}
			if (str[count.i] && str[count.i] == '\"')
				count.i++;
		}
		else if (str[count.i] == '\'')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\'')
			{
				count.counter++;
				count.i++;
			}
			if (str[count.i] && str[count.i] == '\'')
				count.i++;
		}
		else
		{
			count.counter++;
			count.i++;
		}
	}
	return (count.counter);
}

t_shell_s	*assign_tokens(t_shell_s *minishell)
{
	t_counter	count;

	if (!minishell)
		return (NULL);
	if (!minishell->lexer || !minishell->lexer->raw_tokens)
		return (minishell);
	count.i = 0;
	count.j = 0;
	while (minishell->lexer->raw_tokens[count.i])
	{
		free(minishell->lexer->tokens[count.i]);
		minishell->lexer->tokens[count.i] = malloc(sizeof(char) * (token_size2(minishell->lexer->raw_tokens[count.i])) + 1);
		count.k = 0;
		count.j = 0;
		while (minishell->lexer->raw_tokens[count.i][count.j])
		{
			if (minishell->lexer->raw_tokens[count.i][count.j] == '\"')
			{
				count.j++;
				while (minishell->lexer->raw_tokens[count.i][count.j] && minishell->lexer->raw_tokens[count.i][count.j] != '\"')
					minishell->lexer->tokens[count.i][count.k++] = minishell->lexer->raw_tokens[count.i][count.j++];
				if (minishell->lexer->raw_tokens[count.i][count.j] && minishell->lexer->raw_tokens[count.i][count.j] == '\"')
					count.j++;
			}
			else if (minishell->lexer->raw_tokens[count.i][count.j] == '\'')
			{
				count.j++;
				while (minishell->lexer->raw_tokens[count.i][count.j] && minishell->lexer->raw_tokens[count.i][count.j] != '\'')
					minishell->lexer->tokens[count.i][count.k++] = minishell->lexer->raw_tokens[count.i][count.j++];
				if (minishell->lexer->raw_tokens[count.i][count.j] && minishell->lexer->raw_tokens[count.i][count.j] == '\'')
					count.j++;
			}
			else
				minishell->lexer->tokens[count.i][count.k++] = minishell->lexer->raw_tokens[count.i][count.j++];
		}
		minishell->lexer->tokens[count.i][count.k] = '\0';
		count.i++;
	}
	minishell->lexer->tokens[count.i] = NULL;
	return (minishell);
}
	// printf("token[%i] = %s\n", count.i, minishell->lexer->tokens[count.i]);
	// for (int i = 0; i < minishell->lexer->num_of_tokens; i++)
	// 	printf("Token[%i] = %s\n", i, minishell->lexer->tokens[i]);

// t_shell_s	*dollar_sign(t_shell_s *minishell)
// {
// 	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
// 		return (NULL);
// 	minishell = expand_env_variables(minishell);
// 	minishell = assign_tokens(minishell);
// 	return (minishell);
// }

char    *dollar_sign(t_shell_s *minishell, char *cmd_line)
{
    char        *old_cmd_line;
    char        *new_cmd_line;

    // if (!cmd_line || !cmd_line[0] || !minishell)
    //     return (NULL);
	new_cmd_line = ft_strdup(cmd_line);
	old_cmd_line = ft_strdup(new_cmd_line);
	while (is_expandable(new_cmd_line) == TRUE)
	{
		free(new_cmd_line);
		new_cmd_line = expand_token(old_cmd_line);
		free(old_cmd_line);
		old_cmd_line = NULL;
		if (new_cmd_line)
			old_cmd_line = ft_strdup(new_cmd_line);
	}
	if (old_cmd_line != NULL)
		free(old_cmd_line);
	while (is_exit_code_expansion(new_cmd_line) == TRUE)
	{
		old_cmd_line = ft_strdup(new_cmd_line);
		free(new_cmd_line);
		new_cmd_line = expand_exit_code_token(minishell, old_cmd_line);
		free(old_cmd_line);
	}
    return (new_cmd_line);
}

// t_shell_s	*expand_env_variables(t_shell_s *minishell)
// {
// 	t_counter	count;
// 	char		**str;
// 	char		*token;

// 	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
// 		return (NULL);
// 	count.i = 0;
// 	count.k = 0;
// 	while (minishell->lexer->tokens[count.i])
// 	{
// 		// printf("I am here\n");
// 		count.j = 0;
// 		count.x = 0;
// 		if (is_expandable(minishell->lexer->raw_tokens[count.i]) == TRUE)
// 		{
// 			token = ft_strdup(minishell->lexer->raw_tokens[count.i]);
// 			str = malloc(sizeof(char *) * (number_of_expansions(minishell->lexer->raw_tokens[count.i]) + 1));
// 		}
// 		else
// 		{
// 			count.i++;
// 			continue ;
// 		}
// 		while (minishell->lexer->raw_tokens[count.i][count.j])
// 		{
// 			if (minishell->lexer->tokens[count.i][count.j] == '\'')
// 			{
// 				count.j++;
// 				while (minishell->lexer->tokens[count.i][count.j] && minishell->lexer->tokens[count.i][count.j] != '\'')
// 					count.j++;
// 				count.j++;
// 			}
// 			else if (minishell->lexer->tokens[count.i][count.j] == '$')
// 			{
// 				count.j++;
// 				str[count.k] = malloc(sizeof(char) * (get_length_of_env(minishell->lexer->raw_tokens[count.i] + count.j) + 1));
// 				while (minishell->lexer->raw_tokens[count.i][count.j] && (ft_isalnum(minishell->lexer->raw_tokens[count.i][count.j]) || minishell->lexer->raw_tokens[count.i][count.j] != '_'))
// 				{
// 					str[count.k][count.x++] = minishell->lexer->raw_tokens[count.i][count.j++];
// 				}
// 				str[count.k][count.x] = '\0';
// 			}
// 			else
// 				count.j++;
// 		}
// 		if (token != NULL)
// 			free(token);
// 	}
// 	return (minishell);
// }

// t_shell_s   *dollar_sign_env_variables(t_shell_s *minishell)
// {
//     t_counter   count;
//     char        *str;

//     if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens || !minishell->lexer->raw_tokens[0])
//         return (NULL);
//     count.i = 0;
//     while (minishell->lexer->raw_tokens[count.i])
//     {
//         count.j = 0;
//         while (minishell->lexer->raw_tokens[count.i][count.j])
//         {
//             if (minishell->lexer->raw_tokens[count.i][count.j] == '\'')
//             {
//                 count.j++;
//                 while (minishell->lexer->raw_tokens[count.i][count.j] && minishell->lexer->raw_tokens[count.i][count.j] != '\'')
//                     count.j++;
//             }
//             else if (minishell->lexer->tokens[count.i][count.j] == '$' && minishell->lexer->tokens[count.i][count.j + 1])
//             {
//                 count.k = 0;
//                 while (minishell->envp->key[count.k])
//                 {
//                     // if (ft_strncmp(str, minishell->envp.key[count.k], ft_strlen_dollar_sign_env(minishell->envp.key[count.k]) - 1) == 0)
//                     // {
//                     //     str = ft_strdup(minishell->lexer->raw_tokens[count.i]);
//                     //     free(minishell->lexer->raw_tokens[count.i]);
//                     // }
//                     count.k++;
//                 }
//             }
//             count.j++;
//         }
//         count.i++;
//     }
//     return (minishell);
// }

// int is_expandable_env(char *str)
// {
//     t_counter   count;
//     char        *string;

//     if (!str)
//         return (FALSE);
//     count.i = 0;
//     while (str[count.i])
//     {
//         count.j = 0;
//         count.counter = 0;
//         if (str[count.i] == '$')
//         {
//             count.i++;
//             while (str[count.i] && str[count.i] != ' ' && str[count.i] != '\'' && str[count.i] != '\"' && str[count.i] != '$')
//             {
//                 count.counter++;
//                 count.i++;
//             }
//             string = malloc(sizeof(char) * count.counter + 1);
//             count.i -= count.counter;
//             while (str[count.i] && str[count.i] != ' ' && str[count.i] != '\'' && str[count.i] != '\"' && str[count.i] != '$')
//                 string[count.j++] = str[count.j++];
//             string[count.m] = '\0';
//             if (string)
//         }
//         else
//             count.i++;
//     }
// }