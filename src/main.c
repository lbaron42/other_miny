/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Main goal should be to create a parser which divides the input from
	the prompt into multiple word-strings which get forwarded into the
	"check_commands" function which does the rest.	

	if (microshell(new_str, env) != 1)   PERSONAL TESTER FUNCTION
		return (env);		       (CURRENTLY EXCLUDED)		*/

#include "minishell.h"

/*	main.c: 1.	*/
/*	Checking if the declared "exit" command is being paired with arguments,
	display a custom notification instead. This is also to prevent the shell 
	from outputting "exit : command not found" otherwise.			*/

static void	check_for_exit_options(char *str, int i)
{
	i = skip_spaces(str, 0);
	if (!ft_find_word(str, "exit", 0, 0))
		return ;
	i += 4;
	if (empty_check(str, i))
		return ;
	printf("minishell: exit: no options or arguments are supported\n");
	str[0] = 0;
}

/*	main.c: 2.	*/
/*	It is imperative to add a complex strncmp-check for any custom flags
	featuring ($) which were added/created via the export-command.

	Example: $TEST should return the content of this flag.
	Bash hides unrecognized flags, so we'll do the same here.

	Currently, the function only seems to support one command at a time,
	it should be fed multiple strings (containing single words/commands) 
	to fulfill its purpose. Consider this for the finalization!

	IMPORTANT: "define_format" (check "shell_commands") should only commentate 
	on a single command then halt any further interpretations. Ignore further
	arguments/options. This is how bash behaves, we intend to replicate this.

	If the prompt starts with BRACKETS then you need to look inside and
	reformat the prompt-string before returning it to the function.
	Check "brackets_1.c" for further context.				*/

char	**check_commands(char *str, char **env)
{
	char	buffer[1024];
	char	new_str[1024];

	if (check_flag_commands(str, env, 0))
		return (env);
	if (!check_echo_prefix(str))
		env = check_export_unset(str, env);
	check_for_brackets(str, new_str, 0, 0);
	check_for_exit_options(new_str, 0);
	if (!new_str[0])
		return (env);
	if (check_qm_prompt(new_str, 0))
		return (env);
	else if (ft_find_bracketed_flag(new_str))
	{
		rewrite_prompt(new_str, buffer, 0, 0);
		define_format(buffer, env, 0, -1);
	}
	else if (!ft_find_word(new_str, "$", 0, 0))
		env = check_shell_commands(new_str, env, 0);
	return (env);
}

/*	main.c: 3.	*/
/*	Would be smart to include a struct- or flag-check of sorts which prevents
	this function from doing anything if there are processes running, or else
	there might be formatting issues with the line-display for minishell.	

	CTRL-D = EOF (technically not a signal, how would you even catch this?)
	CTRL-C = SIGINT
	CTRL-\ = SIGQUIT							*/

void	sigint_handler(int sig)
{
	signal(sig, SIG_IGN);
	if (sig == SIGINT)
	{
		signal(SIGINT, sigint_handler);
		write (STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		signal(SIGQUIT, sigint_handler);
		return ;
	}
}

/*	main.c: 4.	*/
/*	argc & argv are irrelevant but we still need them to extract envp!

	ft_exit makes sure to free the prompt string, so no worries there.	
	ft_free does return 1, so that part of error-return is taken care of.

	In case of a malloc-fail we need to clear out everything and then
	shut down the program. Do not forget to include the struct(s) which
	we have yet to implement!						*/

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	char		**env;
	t_token	*head = NULL;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	env = copy_env(envp);
	while (env)
	{
		prompt = readline("minishell:) ");
		if (!prompt)
			return (ft_free_array(env));
		if (ft_exit(prompt, env))
			break ;
		if (prompt && !empty_check(prompt, 0))
		{
			add_history(prompt);
			head = create_token_list(prompt, head);
			parser(envp, head);
			head = NULL;
//			env = check_commands(prompt, env);
//			if (!env)
//				return (ft_error(1, prompt, env));
		}
		ft_free(&prompt);
	}
	return (0);
}
