/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:48 by agrun             #+#    #+#             */
/*   Updated: 2023/06/05 10:30:53 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	run_built_in_2.c : 1.	*/

void	rewrite_tmp_3(char **tmp, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			tmp[i][j] = envp[i][j];
			j++;
		}
		tmp[i][j] = 0;
		i++;
	}
	tmp[i][0] = 0;
}

/*	run_built_in_2.c : 2.	*/

void	rewrite_tmp_2(char **tmp, char *buffer, char **envp, int mode)
{
	int	i;
	int	j;

	j = -1;
	if (mode == 2)
	{
		i = -1;
		while (buffer[++i])
			tmp[0][++j] = buffer[i];
		tmp[0][j + 1] = 0;
		tmp[1][0] = 0;
	}
	else if (mode == 3)
		rewrite_tmp_3(tmp, envp);
}

/*	run_built_in_2.c : 3.	*/
/*	This function rewrites the **tmp array if there are any leftovers,
	e.g. if there wasn't a printout due to another operator being on
	the prompt/command line, for that purpose the content from the
	previous function(s) gets stored within tmp for further handling.

	For mode 1 it is necessary to skip past "echo" first.

	Mode 1 = Copies echo string into tmp[0] without echo-prefix & operator.
	Mode 2 = Copies the current work directory into tmp[0].
	Mode 3 = Copies the entirety of envp into tmp.				*/

void	rewrite_tmp(char **tmp, char *buffer, char **envp, int mode)
{
	int	i;
	int	j;

	j = -1;
	if (mode == 1)
	{
		i = 0;
		while (buffer[i] && buffer[i] != ' ' && buffer[i] != 9)
			i++;
		i = skip_spaces(buffer, i + 1) - 1;
		while (buffer[++i] && buffer[i] != '>'
			&& buffer[i] != '<' && buffer[i] != '|')
			tmp[0][++j] = buffer[i];
		tmp[0][j + 1] = 0;
		tmp[1][0] = 0;
	}
	else
		rewrite_tmp_2(tmp, buffer, envp, mode);
}

/*	run_built_in_2.c : 4.	*/

static int	skip_command_path(char **tmp, int j)
{
	while (tmp[0][j] && tmp[0][j] != ' ' && tmp[0][j] != 9)
		j++;
	j--;
	while (tmp[0][j] && tmp[0][j] != '/')
		j--;
	j++;
	return (ft_return(j, 0));
}

/*	run_built_in_2.c : 5.	*/
/*	This function joins all strings within the dimensional one into a 
	single one and then forwards the content to the various subfunctions.

	Spaces are added between the various words/tokens if necessary.
	Basically creates a readable string without the filepath in it.
	Mandatory to make the built-in functions work within minishelll's code. */

void	rewrite_buffer(char **tmp, char *buffer, int i, int x)
{
	int	j;

	while (tmp[i][0])
	{
		j = 0;
		if (i == 0)
			j = skip_command_path(tmp, j);
		while (tmp[i][j])
		{
			buffer[x] = tmp[i][j];
			x++;
			j++;
		}
		if (tmp[i + 1][0] == '>' || tmp[i + 1][0] == '<'
			|| tmp[i + 1][0] == '|')
			break ;
		if (tmp[i + 1][0])
		{
			buffer[x] = ' ';
			x++;
		}
		i++;
	}
	buffer[x] = 0;
}
