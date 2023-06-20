/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	shell_commands.c: 1.	*/
/*	Using the $? commands returns the latest received exit value.
	The input "$?a" should display "1a" for example.
	The $?-check only occurs in this instance if echo requires it.

	Look up "utils_3" for the "ft_find_word" function.
	The "i"-variable serves as a placeholder for various tasks.
			
	Do nothing if you encounter export or unset, these commands
	are being taken care of in the flag/dollar-sign functions.
	These conditions are required to avoid the cmd-error message.		*/

static int	more_shell_commands(char *str, char **envp, int hide_error, int i)
{
	if (ft_strncmp("env", str, 0, 0))
	{
		if (hide_error == 1)
			print_env(envp, 0);
		else
			print_env(envp, 1);
		i = 1;
	}
	else if (ft_find_word(str, "$?", 0, 0))
	{
		check_qm_prompt(str, hide_error);
		i = 1;
	}
	else if (ft_strncmp("history -c", str, 0, 0))
	{
		rl_clear_history();
		i = 1;
	}
	else if (ft_strncmp("export", str, 0, 0) || ft_strncmp("unset", str, 0, 0))
		i = 1;
	return (ft_return(i, 0));
}

/*	shell_commands.c: 2.	*/
/*	The "history" command which usually creates a list of all saved inputs
	isn't part of the project description and as such is to be omitted.	

	It's very important to consider any extra-spaces between the command
	and the option (may it be -c or -n), these are allowed in the original!

	Echo should avoid calling itself which is why it's not available if
	the hide_error flag is set to 1 (only used by echo itself.)
	
	It is imperative that env is returned since it can be altered via the
	CD COMMAND! Make sure to properly update the PWD entry in the env!

	If a command doesn't exist it's vital to ONLY display the start of the
	string and OMIT every further word/command, this is normal behavior.

	One exception is the command "env" however since it isn't supposed to
	support options/further arguments, however writing "env : command n. f."
	would be nonsensical, so it's being omitted. Do nothing in that case.	*/

char	**check_shell_commands(char *str, char **envp, int hide_error)
{
	char	buffer[1024];

	if (hide_error == 0 && ft_strncmp("echo", str, 0, 0))
	{
		if (print_echo(str, 0, 0, envp))
			return (NULL);
	}
	else if (ft_strncmp("cd", str, 0, 0))
		envp = change_directory(str, envp, -1, 0);
	else if (ft_strncmp("pwd", str, 0, 0))
	{
		getcwd(buffer, sizeof(buffer));
		printf("%s", buffer);
		if (hide_error == 0)
			printf("\n");
	}
	else if (more_shell_commands(str, envp, hide_error, 0))
		return (envp);
	else if (hide_error == 0 && !ft_find_word(str, "env", 0, 0))
	{
		adjust_flag_string(str, buffer, 0);
		printf("%s : command not found\n", buffer);
	}
	return (envp);
}

/*	shell_commands.c: 3.	*/
/*	Checking for commands which usually are followed by specific input.
	Check utils_1 (ft_strncmp) for context on that.				

	The command pwd for instance should still work even if arguments or
	further input follows, that stuff should be omitted however.		*/

int	check_extended_shell_commands(char *ref)
{
	if (ref[0] == 'e' && ref[1] == 'c' && ref[2] == 'h' && ref[3] == 'o')
		return (ft_return(1, 0));
	if (ref[0] == 'c' && ref[1] == 'd' && !ref[2])
		return (ft_return(1, 0));
	if (ref[0] == 'u' && ref[1] == 'n' && ref[2] == 's')
		if (ref[3] == 'e' && ref[4] == 't' && !ref[5])
			return (ft_return(1, 0));
	if (ref[0] == 'e' && ref[1] == 'x' && ref[2] == 'p' && ref[3] == 'o')
		if (ref[4] == 'r' && ref[5] == 't' && !ref[6])
			return (ft_return(1, 0));
	if (ref[0] == 'w' && ref[1] == 'c' && ref[2] == ' ')
		if (ref[3] == '-' && ref[4] == 'l')
			return (ft_return(1, 0));
	if (ref[0] == 'l' && ref[1] == 's' && !ref[2])
		return (ft_return(1, 0));
	if (ref[0] == 'r' && ref[1] == 'm' && !ref[2])
		return (ft_return(1, 0));
	if (ref[0] == 'c' && ref[1] == 'a' && ref[2] == 't' && !ref[3])
		return (ft_return(1, 0));
	if (ref[0] == 'p' && ref[1] == 'w' && ref[2] == 'd' && !ref[3])
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	shell_commands.c: 4.	*/

static void	define_format_2(char *str, int i, int j)
{
	char	buffer[1024];

	if (check_qm_prompt(str, 1))
	{
		i = skip_spaces(str, 0) - 1 + 2;
		while (str[++i])
			buffer[++j] = str[i];
		buffer[j + 1] = 0;
		printf("%s : command not found\n", buffer);
	}
	else
	{
		i = skip_spaces(str, 0) - 1;
		while (str[++i])
			buffer[++j] = str[i];
		buffer[j + 1] = 0;
		if (!check_extended_shell_commands(buffer))
			printf("%s : command not found\n", buffer);
	}
}

/*	shell_commands.c: 5.	*/
/*	Only very few commands are supported by this (check main/check_cmds for
	context). The shell will print out a single line generated by the command
	and then commentate on it.

	It will not bother reading any further input beyond that point, only a
	single command will be commentated. This is considered normal behavior.	

	$(pwd) should display the directory and declare it as such, e.g.:		
	minishell: /nfs/homes/agrun/42cursus/level_3/minishell: Is a directory	

	$(env) should display the first array-line and define it this way:
	"bash: SHELL=/bin/bash: No such file or directory"			*/

void	define_format(char *str, char **env, int i, int j)
{
	char	buffer[1024];

	if (ft_find_word(str, "env", 0, 0))
		printf("minishell: %s : No such file or directory\n", env[0]);
	else if (ft_find_word(str, "pwd", 0, 0))
	{
		getcwd(buffer, sizeof(buffer));
		printf("minishell: %s : Is a directory\n", buffer);
	}
	else
		define_format_2(str, i, j);
}
