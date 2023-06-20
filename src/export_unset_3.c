/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_3.c	                	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	export_unset_3.c: 1.	*/
/*	The n-variable is there to determine if a newline should be printed
	at the end or not. Context relies on usage, for instance during echo.	*/

void	print_env(char **env, int n)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!env[i + 1])
			printf("%s", env[i]);
		else
			printf("%s ", env[i]);
		if (n == 1)
			printf("\n");
		else if (n == 2)
		{
			if (env[i + 1])
				printf("\n");
		}
	}
}

/*	export_unset_3.c: 2.	*/
/*	Making sure that the formatting is correct or else there'll be nothing
	to export. This needs to be treated like an error.			

	It's important the equal-sign (=) is in the middle and not at the start
	or end of the string!							*/

static int	check_export_format(char *str)
{
	int	x;
	int	sign_found;

	x = 0;
	sign_found = 0;
	while (str[x])
	{
		if (str[x] == '=' && x != 0)
			sign_found = 1;
		x++;
	}
	if (str[x - 1] == '=')
		sign_found = 0;
	return (ft_return(sign_found, 0));
}

/*	export_unset_3.c: 3.	*/
/*	It is imperative that this function quits if there's nothing after
	either export or unset. Or else there'll be a segfault!			*/

static char	**edit_env(char *str, char **env, int flag, int *i)
{
	char	buf[1024];
	int		mode;
	int		j;

	mode = 0;
	if (flag > 10000)
	{
		flag -= 10000;
		mode = 1;
	}
	i[0] = flag;
	i[0] = skip_spaces(str, flag);
	j = 0;
	while (str[i[0]] && str[i[0]] != ' ' && str[i[0]] != 9)
	{
		buf[j] = str[i[0]];
		j++;
		i[0]++;
	}
	buf[j] = 0;
	if (!mode && check_export_format(buf))
		env = update_env(env, buf, 0);
	else if (mode && buf[0])
		env = update_env(env, buf, 1);
	return (env);
}

/*	export_unset_3.c: 4.	*/

static int	exun_flag_checker(char *str, int *i, int flag)
{
	if (str[i[0]] == 'e')
	{
		if (ft_strncmp("export", str, i[0], 0))
		{
			flag = i[0] + 6;
			i[0] += 6;
		}
	}
	else if (str[i[0]] == 'u')
	{
		if (ft_strncmp("unset", str, i[0], 0))
		{
			flag = i[0] + 5 + 10000;
			i[0] += 5;
		}
	}
	return (ft_return(flag, 0));
}

/*	export_unset_3.c: 5.	*/
/*	Check "main" for context. This function is for catching the "export" and
	"unset" commands.

	Adding +10000 to one of the flag values to differentiate between export
	and unset on the next function.						*/

char	**check_export_unset(char *str, char **env)
{
	int	q[4];
	int	i[2];
	int	flag;

	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	i[0] = skip_spaces(str, 0);
	while (str[i[0]])
	{
		skip_quotes_and_brackets(str, q, i, 0);
		skip_quotes_and_brackets(str, q, i, 1);
		skip_quotes_and_brackets(str, q, i, 2);
		if (str[i[0]] == 'e' || str[i[0]] == 'u')
		{
			flag = -1;
			flag = exun_flag_checker(str, i, flag);
			if (flag > 0)
				env = edit_env(str, env, flag, i);
		}
		if (!env)
			return (NULL);
		i[0]++;
	}
	return (env);
}
