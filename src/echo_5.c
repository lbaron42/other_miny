/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	echo_5.c: 1.	*/
/*	Look up echo_3 for context! This function is used to print out
	format issues with echo input and commands.				*/

int	ft_format_error(char *str, int code, int i, int j)
{
	char	buf[1024];

	if (code == 1)
		printf("minishell: syntax error near unexpected token `('\n");
	else if (code == 2)
	{
		while (str[i] && str[i] != '(')
			i++;
		i++;
		while (str[i] && str[i] != ')')
		{
			buf[j] = str[i];
			j++;
			i++;
		}
		if (str[i + 1] == ')')
		{
			buf[j] = ')';
			j++;
		}
		buf[j] = 0;
		printf("minishell: syntax error near unexpected token `%s'\n", buf);
	}
	return (ft_return(1, 0));
}

/*	echo_5.c: 2.	*/
/*	Look up echo_2 for context! This function checks for known flags and will
	display them if possible. Check flag_commands_2 for "display_found_flag".*/

int	display_known_flags(char *str, int *i, int special, char **env)
{
	char	buffer[1024];
	int		x;
	int		y;

	if (special != 0 || str[i[0] + 1] == '?' || str[i[0] + 1] == '(')
		return (ft_return(0, 0));
	if (str[i[0]] == '$')
		i[0]++;
	x = i[0];
	y = 0;
	buffer[y] = 0;
	while (str[x] && str[x] != ' ' && str[x] != 9)
	{
		buffer[y] = str[x];
		y++;
		x++;
	}
	buffer[y] = 0;
	if (!display_found_flag(buffer, env, -1, 2))
		i[0]++;
	i[0] += y;
	return (ft_return(1, 0));
}
