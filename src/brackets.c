/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	brackets.c: 1.	*/
/*	Support-function for "check_bracket_number". Alters the value of the
	"qm"(quotation mark)-variable.						*/

static void	qm_counter(char *str, int i, int *qm)
{
	if (str[i] == 39 && !qm[1])
	{
		if (!qm[0])
			qm[0] = 1;
		else
			qm[0] = 0;
	}
	else if (str[i] == '"' && !qm[0])
	{
		if (!qm[1])
			qm[1] = 1;
		else
			qm[1] = 0;
	}
}

/*	brackets.c: 2.	*/
/*	Displays an error if the number of brackets is uneven. Highlights the
	odd bracket and then disregards the entire string.			*/

static void	check_bracket_number(char *str, int i, int r_br, int l_br)
{
	int	qm[2];

	qm[0] = 0;
	qm[1] = 0;
	while (str[i])
	{
		if (str[i] == '(' && !qm[0] && !qm[1])
			l_br++;
		if (str[i] == ')' && !qm[0] && !qm[1])
			r_br++;
		qm_counter(str, i, qm);
		i++;
	}
	if (l_br == r_br)
		return ;
	else if (l_br > r_br)
		printf("minishell: syntax error near unexpected token `('\n");
	else if (l_br < r_br)
		printf("minishell: syntax error near unexpected token `)'\n");
	str[0] = 0;
}

/*	brackets.c: 3.	*/
/*	Properly displays syntax errors in case of bracket misuse.		*/

static void	check_bracket_content(char *str, int i, int j)
{
	char	buffer[1024];

	if (str[i] != '(')
		return ;
	i++;
	while (str[i] && str[i] != ')')
		i++;
	while (str[i] == ')')
		i++;
	i = skip_spaces(str, i) - 1;
	if (empty_check(str, i + 1))
	{
		str[0] = 0;
		return ;
	}
	if (str[i + 1] == '(')
		printf("minishell: syntax error near unexpected token `('\n");
	else
	{
		while (str[++i])
			buffer[++j] = str[i];
		buffer[j + 1] = 0;
		printf("minishell: syntax error near unexpected token `%s'\n", buffer);
	}
	str[0] = 0;
}

/*	brackets.c: 4.	*/
/*	If there are brackets at the front and end of the string/prompt, it is
	required to remove them. Bash will run the contents of the brackets as
	if the brackets aren't there, so we need to replicate this behavior.	*/

static int	remove_outer_brackets(char *str, char *new, int i, int j)
{
	int	x;
	int	y;

	if (str[i] != '(')
		return (ft_return (0, 0));
	x = i + 1;
	while (str[i])
		i++;
	i--;
	while (str[i] && (str[i] == ' ' || str[i] == 39))
		i--;
	if (str[i] != ')')
		return (ft_return (0, 0));
	y = i;
	while (x < y)
	{
		new[j] = str[x];
		j++;
		x++;
	}
	new[j] = 0;
	return (ft_return (1, 0));
}

/*	brackets.c: 5.	*/
/*	If there are multiple brackets within a bracketed prompt the content
	needs to be omitted. Example: ((pwd)) -> does nothing. If there are
	single brackets "(pwd)" it's necessary to remove just these brackets.

	"(pwd)" on its own should behave like "pwd", however if ANYTHING 
	follows afterwards it needs to be treated like a syntax error!

	e.g.: (env) pwd => bash: syntax error near unexpected token `pwd'
	e.g.: (env) (pwd) => bash: syntax error near unexpected token `('

	If there's a dollar-sign in front of a bracket, do NOT alter anything.
	The "check_commands"-function will take care of the rest.		*/

void	check_for_brackets(char *str, char *new, int i, int j)
{
	new[0] = 0;
	i = skip_spaces(str, 0);
	if (!remove_outer_brackets(str, new, i, 0))
	{
		while (str[i])
		{
			new[j] = str[i];
			j++;
			i++;
		}
		new[j] = 0;
	}
	i = skip_spaces(new, 0);
	j = i;
	i = skip_flags(new, i);
	if (j == i)
	{
		check_bracket_number(new, i, 0, 0);
		check_bracket_content(new, i, -1);
	}
}
