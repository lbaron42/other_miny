/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                       	                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	utils_4.c: 1.	*/
/*	Look up echo_2 for context. This is mainly used to shorten the number
	of used lines on the handle_dollar_sign function.			*/

int	check_alpha_num(char *echo, int *i)
{
	if (echo[i[0] + 1] >= '0' && echo[i[0] + 1] <= '9')
		return (ft_return(0, 0));
	else if (echo[i[0] + 1] >= 'A' && echo[i[0] + 1] <= 'Z')
		return (ft_return(0, 0));
	else if (echo[i[0] + 1] >= 'a' && echo[i[0] + 1] <= 'z')
		return (ft_return(0, 0));
	return (ft_return(1, 0));
}

/*	utils_4.c: 2.	*/
/*	This makes sure that the whole input will be displayed, for instance:
	$?a -> [last returned value]a -> "0a" (as an example).

	The error-message ("Command not found") only refers to the first word
	and will omit the rest of the string, this is normal behavior.		*/

void	adjust_flag_string(char *str, char *buf, int i)
{
	int	x;

	x = 0;
	while (str[i] && str[i] != ' ' && str[i] != 9)
	{
		buf[x] = str[i];
		x++;
		i++;
	}
	buf[x] = 0;
}

/*	utils_4.c: 3.	*/
/*	Using the $? commands returns the latest received exit value.
	The input "$?a" should display "1a" for example.
	The command used on its own will return an error however.		*/

int	check_qm_prompt(char *str, int hide_error)
{
	char	buf[1024];
	int		i;

	if (ft_find_word(str, "$?", 0, 0))
	{
		printf("%d", ft_return(0, 1));
		i = skip_spaces(str, 0);
		i += 2;
		adjust_flag_string(str, buf, i);
		if (hide_error == 0)
			printf("%s : command not found\n", buf);
		return (ft_return(1, 0));
	}
	return (ft_return(0, 0));
}

/*	utils_4.c: 4.	*/
/*	This function will only skip flags if they're properly formatted,
	else the original i-value will be returned to avoid complications.	*/

int	skip_flags(char *str, int i)
{
	int	j;

	j = i;
	if (str[j] == '$' && str[j + 1] == '(')
	{
		j++;
		while (str[j] && str[j] != ')')
		{
			if (str[j] == '$' || str[j] == '(')
				return (i);
			else
				j++;
		}
		if (str[j] == ')')
			return (j + 1);
		return (i);
	}
	return (i);
}

/*	utils_4.c: 5.	*/

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == 9))
		i++;
	return (ft_return(i, 0));
}
