/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'lexer_utils_2.c'                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-06-11 02:12:34 by lbaron            :+:    #+#             */
/*   Updated: 2023-06-11 02:12:34 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void	handle_pipe(char c, t_token *token)
{
	char	value[2];

	value[0] = c;
	value[1] = '\0';
	*token = createtoken(TOKEN_PIPE, value);
}

void	handle_redirection_in(char c, t_token *token)
{
	char	value[2];

	value[0] = c;
	value[1] = '\0';
	*token = createtoken(TOKEN_REDIRECTION_IN, value);
}

void	handle_redirection_out(char c, t_token *token)
{
	char	value[2];

	value[0] = c;
	value[1] = '\0';
	*token = createtoken(TOKEN_REDIRECTION_OUT, value);
}

void	handle_space(char c, t_token *token)
{
	char	value[2];

	value[0] = c;
	value[1] = '\0';
	*token = createtoken(TOKEN_SPACE, value);
}

void	handlesinglecharactertoken(char c, t_token *token)
{
	const t_tokenhandler	handlers[] = {
		handle_pipe,
		handle_redirection_in,
		handle_redirection_out,
		handle_space
	};
	size_t					num_handlers;
	int						i;

	num_handlers = sizeof(handlers) / sizeof(handlers[0]);
	i = 0;
	while (i < num_handlers)
	{
		if (c == '|' && handlers[i] == handle_pipe)
			handlers[i](c, token);
		else if (c == '<' && handlers[i] == handle_redirection_in)
			handlers[i](c, token);
		else if (c == '>' && handlers[i] == handle_redirection_out)
			handlers[i](c, token);
		else if (c == ' ' && handlers[i] == handle_space)
			handlers[i](c, token);
		i++;
	}
}
