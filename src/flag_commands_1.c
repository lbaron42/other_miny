/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_commands_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	flag_commands_1.c: 1.	*/

static void	found_flag_command(char *str, char **env, int *i, int hide_e)
{
	char	buf[1024];
	int		x;
	int		y;
	int		z;

	x = i[0];
	y = -1;
	while (str[i[0]])
	{
		if (str[i[0]] == ' ' || str[i[0]] == 9)
			break ;
		i[0]++;
	}
	y = i[0] - 1;
	z = -1;
	while (++x <= y)
		buf[++z] = str[x];
	buf[z + 1] = 0;
	display_found_flag(buf, env, -1, hide_e);
}

/*	flag_commands_1.c: 2.	*/
/*	Checking for single/double-quotation makes as well as brackets.		*/

void	skip_quotes_and_brackets(char *str, int *flag, int *i, int n)
{
	char	m;

	if (n == 0)
		m = 39;
	else if (n == 1)
		m = '"';
	else
		m = '(';
	if (str[i[0]] == m)
	{
		if (str[i[0]] == '(')
			m = ')';
		flag[n] = 1;
		while (str[i[0]] && str[i[0]] != m)
		{
			if (str[i[0]] == m)
			{
				flag[n] = 0;
				break ;
			}
			i[0]++;
		}
	}
}

/*	flag_commands_1.c: 3.	*/

static void	set_flag_variables(int *flag, int *i)
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	i[0] = 0;
}

/*	flag_commands_1.c: 4.	*/
/*	Checking for anything with a dollar-sign in front of it.
	Usually this refers to content within envp, this also includes
	custom-set flags created via the export-command. Check for those!

	It is important to check for quotation marks and brackets, they are
	against the supported format of flags.

	The export-command without any further input should only print out the
	current version of env - respect custom additions done via "export"!	*/

int	check_flag_commands(char *str, char **env, int hide_e)
{
	int		flag[4];
	int		i[2];
	int		r;

	r = 0;
	if (check_echo_prefix(str))
		return (ft_return(r, 0));
	set_flag_variables(flag, i);
	while (str[i[0]])
	{
		skip_quotes_and_brackets(str, flag, i, 0);
		skip_quotes_and_brackets(str, flag, i, 1);
		skip_quotes_and_brackets(str, flag, i, 2);
		if (str[i[0]] == '$' && !flag[0] && !flag[1] && !flag[2])
		{
			found_flag_command(str, env, i, hide_e);
			r = 1;
		}
		i[0]++;
	}
	return (ft_return(r, 0));
}
