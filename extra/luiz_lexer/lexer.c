/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'lexer.c'                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-10 23:44:30 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-10 23:44:30 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void	handleflagtoken(char *input, int *index, t_token *token)
{
	char	value[MAX_TOKEN_LENGTH];
	int		i;
	char	c;

	i = 0;
	c = '-';
	value[i++] = c;
	while (c != '\0' && c != ' ' && c != '|' && c != '<' && c != '>')
	{
		c = input[++(*index)];
		value[i++] = c;
	}
	value[i] = '\0';
	*token = createtoken(TOKEN_FLAG, value);
	(*index)--;
}

void	handlecommandorargumenttoken(char *input, int *index, t_token *token)
{
	char	value[MAX_TOKEN_LENGTH];
	int		i;
	char	c;

	i = 0;
	c = input[*index];
	while (c != '\0' && c != ' ' && c != '|' && c != '<' && c != '>')
	{
		value[i++] = c;
		c = input[++(*index)];
	}
	value[i] = '\0';
	(*index)--;
	if (iskeyword(value))
	{
		*token = createtoken(TOKEN_COMMAND, value);
	}
	else
	{
		*token = createtoken(TOKEN_ARGUMENT, value);
	}
}

t_token	getnexttoken(char *input, int *index)
{
	t_token	token;
	char	c;

	c = input[*index];
	if (c == '\0')
	{
		return (createtoken(-1, ""));
	}
	if (c == '<' || c == '>')
	{
		handledoublechartoken(input, index, c, &token);
	}
	else if (c == '|' || c == '<' || c == '>' || c == ' ')
	{
		handlesinglecharactertoken(c, &token);
	}
	else if (c == '-')
	{
		handleflagtoken(input, index, &token);
	}
	else
	{
		handlecommandorargumenttoken(input, index, &token);
	}
	return (token);
}
