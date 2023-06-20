/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'lexer_utils.c'                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-11 00:26:53 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-11 00:26:53 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

int	iskeyword(const char *identifier)
{
	int			i;
	int			numkeywords;
	const char	*keywords[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset",
		"grep", "wc", "mkdir", "mv", "cp", "rm", "rmdir", "touch",
		"find", "head", "tail", "diff", "find", "cat"
	};

	numkeywords = sizeof(keywords) / sizeof(keywords[0]);
	i = 0;
	while (i < numkeywords)
	{
		if (strcmp(identifier, keywords[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

t_token	createtoken(t_tokenType type, char value[])
{
	t_token	token;

	token.type = type;
	strcpy(token.value, value);
	return (token);
}

void	handledoublechartoken(char *input, int *index, char c, t_token *token)
{
	char	value[3];

	value[0] = c;
	value[1] = c;
	value[2] = '\0';
	if (c == '<' && input[*index + 1] == '<')
	{
		*token = createtoken(TOKEN_HERE_DOC, value);
		(*index)++;
	}
	else if (c == '>' && input[*index + 1] == '>')
	{
		*token = createtoken(TOKEN_APPEND_DOC, value);
		(*index)++;
	}
	else
	{
		handlesinglecharactertoken(c, token);
	}
}

void	handlevariablecharactertoken(char *input, int *index, t_token *token)
{
	char	c;

	c = input[*index];
	if (c == '-')
	{
		handleflagtoken(input, index, token);
	}
	else
	{
		handlecommandorargumenttoken(input, index, token);
	}
}
