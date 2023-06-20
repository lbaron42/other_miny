/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_1.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	echo_1.c: 1.	*/
/*	This function is required for echo_3, look it up for context.		*/

int	check_next_quotation_mark(char *echo, int i, int mode)
{
	int	f;
	int	q[2];

	f = 0;
	q[0] = 39;
	q[1] = '"';
	if (mode)
	{
		q[0] = '"';
		q[1] = 39;
	}
	i--;
	while (echo[++i] && echo[i] != q[0])
	{
		if (echo[i] == q[1] && !f)
			f = 1;
		if (echo[i] == q[1] && !f)
			f = 1;
	}
	if (echo[i] != q[0] || q[1])
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	echo_1.c: 2.	*/
/*	Going through the array until arriving at the end of "echo",
	checking if -n follows afterwards.					*/

static int	check_n_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != 'o')
		i++;
	i++;
	while ((str[i] == ' ' || str[i] == 9) && str[i] != '-')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}

/*	echo_1.c: 3.	*/
/*	Attention: "echo" does print an empty line in the original function
	if there's no further input beyond the echo command!

	IMPORTANT: the echo-function hides single layered quotation marks.	*/

static int	check_echo_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != 'o')
		i++;
	i++;
	if (check_n_flag(str))
	{
		while (str[i] && str[i] != 'n')
			i++;
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == 9))
		i++;
	return (ft_return(i, 0));
}

/*	echo_1.c: 4.	*/
/*	Using integer arrays since these can be updated/changed across 
	functions without needing to return their value. Very useful.

	We'll be needing those to keep check of characters like single
	and double quotation marks as well as handling the "i" and "j"
	integers for the echo and buffer strings on the next function.		*/

static void	echo_flag_setup(int *x, int *q_flag)
{
	x[0] = 0;
	x[1] = 0;
	q_flag[0] = 0;
	q_flag[1] = 0;
}

/*	echo_1.c: 5.	*/
/*	The echo command doesn't print quotation marks, however it will 
	refuse to work if there's an uneven number of them in the string!

	Make sure to consider -n as an option for echo, in that case omit
	the newline-bit ('\n').

	Using an additional flag (neg. value for x[0]) to avoid additional
	newlines since the printf used on echo_2 deals with that already
	in case it encounters an error with echo.

	If malloc fails you should clear out the envp and return (1),
	the main function will interpret this as a malloc failure and
	do the rest to properly shut down minishell.				*/

int	print_echo(char *str, int i, int j, char **envp)
{
	int		x[2];
	int		q_flag[2];
	char	*echo;

	echo_flag_setup(x, q_flag);
	i = check_echo_start(str);
	j = i;
	while (str[i])
		i++;
	echo = malloc(sizeof(char) * (i - j + 1));
	if (!echo)
		ft_free_array(envp);
	if (!echo)
		return (ft_return(1, 0));
	i = -1;
	j--;
	while (str[++j])
		echo[++i] = str[j];
	echo[i + 1] = 0;
	display_echo_errors(echo, -1, 0);
	handle_echo_rules(echo, x, q_flag, envp);
	if (!check_n_flag(str) && x[0] > 0)
		printf("\n");
	ft_free(&echo);
	return (ft_return(0, 0));
}
