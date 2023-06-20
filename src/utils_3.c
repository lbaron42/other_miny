/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_3.c: 1.	*/
/*	Using this function to store and return the last used exit value.
	Use mode (1) if you want to extract the value without overwriting.	*/

int	ft_return(int r, int mode)
{
	static int	ret;

	if (!mode)
		ret = r;
	return (ret);
}

/*	utils_3.c: 2.	*/
/*	Check main (see "check_commands") for further context.			*/

void	rewrite_prompt(char *str, char *buffer, int i, int j)
{
	i = skip_spaces(str, i) + 2;
	while (str[i] && str[i] != ')')
	{
		buffer[j] = str[i];
		j++;
		i++;
	}
	buffer[j] = 0;
}

/*	utils_3.c: 3.	*/

int	ft_find_word(char *str, char *ref, int i, int j)
{
	i = skip_spaces(str, i);
	while (str[i])
	{
		if (str[i] == ref[j])
			j++;
		else
			break ;
		i++;
	}
	if (!ref[j])
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	utils_3.c: 4.	*/
/*	Used for finding dollar-sign flags (e.g.: "$(pwd)").
	Check main (check_commands function) for further context.		*/

int	ft_find_bracketed_flag(char *str)
{
	int	i;

	if (!ft_find_word(str, "$(", 0, 0))
		return (ft_return(0, 0));
	i = skip_spaces(str, 0) + 2;
	while (str[i] && str[i] != '(' && str[i] != ')')
		i++;
	if (i && str[i] == ')')
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	utils_3.c: 5.	*/
/*	If echo is at the front of the string it'd be preferable to bypass
	the export/unset-check and look up the other command-subfunctions via 
	the respective echo-support-functions. 		CHECK MAIN FOR CONTEXT.	*/

int	check_echo_prefix(char *str)
{
	int	i;

	i = skip_spaces(str, 0);
	if (ft_strncmp("echo", str, i, 0))
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}
