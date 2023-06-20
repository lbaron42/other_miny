/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:48 by agrun             #+#    #+#             */
/*   Updated: 2023/06/05 10:30:53 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	run_built_in_1.c : 1.	*/
/*	If there's a redirector appearing it's not necessary to see if it's
	an appending type (>> || <<) since all that matters is that another
	operator has been found. We return (0) in that case.			*/

int	check_next_operator(char **str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i][0] == '>' || str[i][0] == '<' || str[i][0] == '|')
			flag = 0;
		i++;
	}
	return (ft_return(flag, 0));
}

/*	run_built_in_1.c : 2.	*/
/*	If you're using PWD or ENV, it is VERY important to consider the context.
	Is there a redirector or pipe coming up? If yes, printing out ENVP/PWD
	might be a bad idea. Simply store their content(s) instead.

	It's also important to print out a N-BYTE at the end of everything, this
	however doesn't occur in this function. It needs to happen at the end
	of reading the entire command-line/prompt before returning to main.

	Mode 1 = PWD
	Mode 2 = ENV								*/

void	run_pwd_env(char **tmp, char **envp, int mode)
{
	int		print;
	char	tmp2[1024];

	print = check_next_operator(tmp);
	if (mode == 1)
	{
		getcwd(tmp2, sizeof(tmp2));
		if (print)
		{
			printf("%s ", tmp2);
			tmp[0][0] = 0;
		}
		else
			rewrite_tmp(tmp, tmp2, NULL, 2);
	}
	else if (mode == 2)
	{
		if (print)
		{
			print_env(envp, 0);
			tmp[0][0] = 0;
		}
		else
			rewrite_tmp(tmp, tmp2, envp, 3);
	}
}

/*	run_built_in_1.c : 3.	*/
/*	The different modes and what they mean:
	1 = CD command
	2 = EXPORT & UNSET
	3 = ECHO command

	It is vital that ECHO only gets used if there are no further redirects 
	or pipes, the PRINTOUT cannot be prevented! Otherwise simply keep what 
	comes after the echo command/token and forward it to another function.

	For that purpose tmp will be rewritten, otherwise wipe it out if it
	has served its purpose. It's up to the code to decide what to do next 
	after leaving this function since tmp will have leftover for the next 
	operator string.

	ENVP is essential for all of these functions since they interact 
	and sometimes also modify it, that's why it needs to be returned.
	Modifications to ENVP only get saved if the dimensional array gets 
	returned all the way back to the main. Please keep that in mind!	

	IMPORTANT: IF (!ENVP) => CORRUPTION DETECTED. SHUT DOWN MINISHELL!	*/

char	**run_cd_export_unset_echo(char **tmp, char **envp, int mode)
{
	char	buffer[1024];
	int		print;

	print = check_next_operator(tmp);
	rewrite_buffer(tmp, buffer, 0, 0);
	if (mode == 1)
		envp = change_directory(buffer, envp, -1, 0);
	else if (mode == 2)
		envp = check_export_unset(buffer, envp);
	else if (mode == 3)
	{
		if (print)
			print_echo(buffer, 0, 0, envp);
		else
			rewrite_tmp(tmp, buffer, NULL, 1);
	}
	if (mode == 1 || mode == 2 || print == 1)
		tmp[0][0] = 0;
	if (!envp)
		return (NULL);
	return (envp);
}

/*	run_built_in_1.c : 4.	*/
/*	This function skips the commandpath and checks the commandname.		*/

static int	skip_and_search(char *str, char *ref, int i, int x)
{
	while (str[i] && str[i] != ' ' && str[i] != 9)
		i++;
	while (ref[x])
		x++;
	x--;
	i--;
	while (str[i])
	{
		if (str[i] == ref[x])
			x--;
		if (x == -1)
			return (ft_return (1, 0));
		i--;
	}
	return (ft_return(0, 0));
}

/*	run_built_in_1.c : 5.	*/
/*	Checking if any built-in commands are mentioned in the tmp-array.

	These functions will either wipe or alter the contents of the tmp after
	running, in that case it's important to check in the code after running
	this function if tmp[0][0]++ still exist. If yes, there's an output that
	needs to be processed further, usually by the next operator.		*/

char	**run_built_in(char **tmp, char **envp)
{
	if (skip_and_search(tmp[0], "cd", 0, 0))
		envp = run_cd_export_unset_echo(tmp, envp, 1);
	else if (skip_and_search(tmp[0], "export", 0, 0))
		envp = run_cd_export_unset_echo(tmp, envp, 2);
	else if (skip_and_search(tmp[0], "unset", 0, 0))
		envp = run_cd_export_unset_echo(tmp, envp, 2);
	else if (skip_and_search(tmp[0], "echo", 0, 0))
		envp = run_cd_export_unset_echo(tmp, envp, 3);
	else if (skip_and_search(tmp[0], "pwd", 0, 0))
		run_pwd_env(tmp, envp, 1);
	else if (skip_and_search(tmp[0], "env", 0, 0))
		run_pwd_env(tmp, envp, 2);
	if (!envp)
		return (NULL);
	return (envp);
}
