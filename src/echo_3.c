/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_3.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	echo_3.c: 1.	*/

static int	flag_checker(char *echo, int i, int q_flag, int mode)
{
	if (!mode)
	{
		if (!q_flag && echo[i] == '"')
			return (ft_return(1, 0));
		else if (!q_flag && echo[i] == '"')
			return (ft_return(0, 0));
	}
	else if (mode)
	{
		if (!q_flag && echo[i] == 39)
			return (ft_return(1, 0));
		else if (!q_flag && echo[i] == 39)
			return (ft_return(0, 0));
	}
	return (ft_return(-1, 0));
}

/*	echo_3.c: 2.	*/

static int	check_format_3(char *echo, int i, int b)
{
	int	qf[3];

	qf[0] = 0;
	qf[1] = 0;
	while (echo[i])
	{
		if (echo[i] == 39)
			qf[0] = flag_checker(echo, i, qf[0], 1);
		if (echo[i] == '"')
			qf[1] = flag_checker(echo, i, qf[1], 0);
		if (echo[i] == '(' && echo[i - 1] != '$' && !qf[0] && !qf[1])
		{
			if (b != 1)
				b = 1;
			else
				return (ft_format_error(echo, 1, 0, 0));
		}
		if (echo[i] == ')' && echo[i - 1] != '$' && !qf[0] && !qf[1])
			if (b == 1)
				b = 0;
		i++;
	}
	if (b != -1)
		return (ft_format_error(echo, 2, 0, 0));
	return (ft_return(0, 0));
}

/*	echo_3.c: 3.	*/

static int	check_format_2(char *echo, int i, int flag, int *x)
{
	int	q;

	q = 0;
	while (echo[i])
	{
		if (echo[i] == '"')
			q = flag_checker(echo, i, q, 0);
		else if (echo[i] == 39)
			flag = flag_checker(echo, i, flag, 1);
		if (echo[i] == '(' && echo[i - 1] != '$' && (!q || !flag))
		{
			if (q && !check_next_quotation_mark(echo, i, 0))
				x[0] = -42;
			else if (flag && !check_next_quotation_mark(echo, i, 1))
				x[0] = -42;
			if (x[0] < 0)
			{
				printf("minishell: syntax error near unexpected token `('\n");
				return (ft_return(1, 0));
			}
		}
		i++;
	}
	return (ft_return(0, 0));
}

/*	echo_3.c: 4.	*/

static int	check_format_1(char *echo, int i, int flag, int *x)
{
	int	q;

	q = 0;
	while (echo[i])
	{
		if (q == 0 && echo[i] == '"')
			q = 1;
		if (q == 1 && echo[i] == '"')
			q = 0;
		if (flag == 0 && q == 0 && echo[i] == 39)
			flag = 1;
		if (flag == 1 && q == 0 && echo[i] == 39)
			flag = 0;
		i++;
	}
	if (flag == 0 && q == 0)
		return (ft_return(0, 0));
	printf("minishell: syntax error with open quotes\n");
	x[0] = -42;
	return (ft_return(1, 0));
}

/*	echo_3.c: 5.	*/
/*	Single quotation marks can still be printed if there are double
	quotation marks around them! Check echo "'" for example.

	echo "'$(pwd)'" should RUN the embedded command in single q-marks!
	echo '$(pwd)' should PRINT the input without the single q-marks!

	echo "'test'" should display 'test'!					*/

int	check_echo_errors(char *echo, int *x)
{
	if (check_format_1(echo, 0, 0, x))
		return (ft_return(1, 0));
	if (check_format_2(echo, 0, 0, x))
		return (ft_return(1, 0));
	if (check_format_3(echo, 0, -1))
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}
