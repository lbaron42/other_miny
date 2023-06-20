/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_4.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	echo_4.c: 1.	*/
/*	Look up echo_2 for context. Only use this function during an echo 
	printout without any "$(" suffix.					*/

int	handle_qm(int *i)
{
	int	ret;

	ret = ft_return(0, 1);
	printf("%d", ret);
	i[0] += 2;
	return (ft_return(1, 0));
}

/*	echo_4.c: 2.	*/
/*	This function checks for supported commands. Open to changes/updates.	*/

int	check_available_commands(char *buf)
{
	if (ft_strncmp("cd", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("rm", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("echo", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("pwd", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("env", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("unset", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("export", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("ls", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("wc -l", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("cat", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("$?", buf, 0, 0))
		return (ft_return(1, 0));
	else if (ft_strncmp("history -c", buf, 0, 0))
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	echo_4.c: 3.	*/

static void	print_echo_error(char *buf, char *echo, int start, int end)
{
	int	j;

	j = -1;
	while (++start <= end)
		buf[++j] = echo[start];
	buf[j + 1] = 0;
	if (!check_available_commands(buf))
		printf("%s : command not found\n", buf);
}

/*	echo_4.c: 4.	*/

static int	handle_echo_flags(char *echo, int i, int mode, int flag)
{
	if (mode == 0)
	{
		if (!flag && echo[i] == 39)
			flag = 1;
		else if (flag && echo[i] == 39)
			flag = 0;
	}
	else
		if (echo[i] == 39)
			return (ft_return(0, 0));
	return (ft_return(mode, 0));
}

/*	echo_4.c: 5.	*/
/*	This function will display unrecognized commands as errors
	before printing out the whole echo line. This is normal behavior.	

	Integer "i" should be at -1 to enable proper functionality!		*/

void	display_echo_errors(char *echo, int i, int flag)
{
	char	buf[1024];
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (echo[++i])
	{
		flag = handle_echo_flags(echo, i, 0, flag);
		start = handle_echo_flags(echo, i, start, flag);
		end = handle_echo_flags(echo, i, end, flag);
		if (echo[i] == '(' && echo[i - 1] == '$')
			start = i;
		if (echo[i] == ')')
			end = i - 1;
		if (start && end)
		{
			print_echo_error(buf, echo, start, end);
			start = 0;
			end = 0;
		}
	}
}
