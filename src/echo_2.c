/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	echo_2.c: 1.	*/
static int	handle_command_printout(char *str, int *i, int special, char **envp)
{
	char	buf[1024];

	if (special != 2)
		return (ft_return(0, 0));
	i[1] = 0;
	i[0] += 2;
	while (str[i[0]] && str[i[0]] != ')' && str[i[0]] != ' ' \
		&& str[i[0]] != 9)
	{
		buf[i[1]] = str[i[0]];
		i[1]++;
		i[0]++;
	}
	if (str[i[0]] == ')')
	{
		buf[i[1]] = 0;
		check_shell_commands(buf, envp, 1);
		i[0]++;
	}
	else
	{
		buf[i[1]] = 0;
		printf("%s", buf);
	}
	return (ft_return(1, 0));
}

/*	echo_2.c: 2.	*/
/*	Print the dollar-sign if you encounter a non-letter or -number
	character right afterwards, otherwise hide the "word" following it!	

	The real echo command  will run shell-commands if they're formatted 
	like this: $(CMD)

	"$?" is an exception and will always work, even without brackets.
	Use "handle_qm" to deal with such instances, resume printing then.
	Look up echo_4 for "handle_qm" and utils_4 for "check_alpha_num".	*/

static void	handle_dollar_sign(char *echo, int *i, int *q_flag, char **envp)
{
	int	special;

	special = 1;
	if (!q_flag[0] && echo[i[0]] == '$')
	{
		if (echo[i[0] + 1] == '(' || echo[i[0] + 1] == '?')
			special = 2;
		else
			special = check_alpha_num(echo, i);
	}
	if (special == 0 && display_known_flags(echo, i, special, envp))
		return ;
	if (special == 2 && echo[i[0] + 1] == '?')
		special = handle_qm(i);
	if (handle_command_printout(echo, i, special, envp))
		return ;
	while (!q_flag[0] && echo[i[0]] && echo[i[0]] != ' ' \
		&& echo[i[0]] != 9 && echo[i[0]] != '"')
	{
		if (special == 1)
			printf("%c", echo[i[0]]);
		i[0]++;
	}
	if (q_flag[1] && echo[i[0]] == '"')
		q_flag[1] = 0;
}

/*	echo_2.c: 3.	*/
static void	handle_double_quotes(char *str, int *i, int *quote_flag)
{
	int	x;

	while (str[i[0]] == '"')
	{
		if (quote_flag[1] == 1)
			quote_flag[1] = 0;
		else
			quote_flag[1] = 1;
		i[0]++;
	}
	if (quote_flag[1] == 0)
		return ;
	x = i[0] - 1;
	while (str[++x])
		if (str[x] == '"')
			x = -42;
	if (x > -1)
		return ;
	while (str[i[0]] && str[i[0]] != ' ' && str[i[0]] != '"' \
		&& str[i[0]] != '$')
	{
		printf("%c", str[i[0]]);
		i[0]++;
	}
}

/*	echo_2.c: 4.	*/
/*	Using a while-loop in case multiple single quotation marks are next
	to each other. Doing the same with double quotation marks (see above).	

	Single quotation marks have the ASCII-value 39.
	Might need to revisit this function, final if-condition (39) is sus.	*/

static void	handle_single_quotes(char *str, int *i, int *quote_flag)
{
	int	x;

	while (str[i[0]] == 39)
	{
		if (quote_flag[0] == 1)
			quote_flag[0] = 0;
		else
			quote_flag[0] = 1;
		i[0]++;
	}
	if (quote_flag[0] == 0)
		return ;
	x = i[0] - 1;
	while (str[++x])
		if (str[x] == 39)
			x = -42;
	if (x > -1)
		return ;
	while (str[i[0]] && str[i[0]] != ' ' && str[i[0]] != 9 && str[i[0]] != 39)
	{
		printf("%c", str[i[0]]);
		i[0]++;
	}
	if (str[i[0]] == 39)
		i[0]++;
}

/*	echo_2.c: 5.	*/
/*	Print quotation marks if they have single quotes (') as suffix!

	The real echo command does interpret words within brackets
	as a syntax error if there's no dollar sign in front of them.

	minishell: syntax error near unexpected token `('
	echo ("'help me'") => minishell: syntax error near unexpected token '[str]'

	^ Use this to display the first error, ignore the rest of the string. 
	Using an error-flag (-42) to avoid additional NL-prints on print_echo.	*/

void	handle_echo_rules(char *echo, int *i, int *quote_flag, char **envp)
{
	if (check_echo_errors(echo, i))
		return ;
	i[0] = 0;
	while (echo[i[0]])
	{
		handle_single_quotes(echo, i, quote_flag);
		handle_double_quotes(echo, i, quote_flag);
		handle_dollar_sign(echo, i, quote_flag, envp);
		if (echo[i[0]] == ' ' || echo[i[0]] == 9)
		{
			printf("%c", echo[i[0]]);
			i[0]++;
		}
	}
}
