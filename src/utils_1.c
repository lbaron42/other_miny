/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_1.c: 1.	*/
/*	It is essential to skip through any spaces if there are any between
	the command and an option (-c or -n), the original commands allow this!	*/

int	ft_strncmp(char *ref, char *input, int i, int j)
{
	i = skip_spaces(input, i);
	while (input[i])
	{
		if (input[i] == ref[j])
		{
			j++;
			i++;
		}
		else
			return (ft_return(0, 0));
		if (!ref[j])
			break ;
		if (input[i - 1] == ' ' && (input[i] == ' ' || input[i] == 9))
			i = skip_spaces(input, i);
	}
	if (ref[j])
		return (ft_return(0, 0));
	if (check_extended_shell_commands(ref))
		return (ft_return(1, 0));
	i = skip_spaces(input, i);
	if (input[i] != 0)
		return (ft_return(0, 0));
	return (ft_return(1, 0));
}

/*	utils_1.c: 2.	*/
/*	Making sure the rest of the input/line contains no further characters.	*/

int	empty_check(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == 9)
			i++;
		else
			return (ft_return(0, 0));
	}
	return (ft_return(1, 0));
}

/*	utils_1.c: 3.	*/

int	ft_exit(char *str, char **env)
{
	if (ft_strncmp("exit", str, 0, 0))
	{
		rl_clear_history();
		ft_free(&str);
		ft_free_array(env);
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	utils_1.c: 4.	*/
/*	This function needs to be extended to include free-instructions
	for the struct we've yet to implement. Shut down minishell if
	malloc fails.								*/

int	ft_error(int error, char *prompt, char **env)
{
	write (2, "Error\n", 6);
	if (error == 1)
		write (2, "Malloc failed.\n", 15);
	rl_clear_history();
	if (prompt)
		ft_free(&prompt);
	if (env)
		ft_free_array(env);
	return (ft_return(1, 0));
}
