/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_commands_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	flag_commands_2.c: 1.	*/
/*	You need to convert the flags into whatever content they have within 
	the env array. Also make sure to hide unknown flags!
	e.g.: $TEST => (nothing), not even an error.

	Remember, if a known flag is being used on its own you need to display
	an error, for example: $USER => "Command 'root' not found"		*/

static void	convert_flag(char *buf, char **env, int i, int hide_e)
{
	int		x;
	int		j;

	j = 0;
	x = -1;
	while (env[i][j] != '=')
		j++;
	if (env[i][j + 1] == '"')
		j++;
	while (env[i][++j])
		buf[++x] = env[i][j];
	if (buf[x] == '"')
		x--;
	buf[x + 1] = 0;
	if (hide_e == 0)
		printf("Command '%s' not found\n", buf);
	else if (hide_e == 1 && buf[0])
		printf("%s ", buf);
	else if (hide_e == 2 && buf[0])
		printf("%s", buf);
}

/*	flag_commands_2.c: 2.	*/
/*	Checking the env-array if the flag is in there. Displaying if yes.
	Hiding double quotation marks at the start and end of flag.		*/

int	display_found_flag(char *buf, char **env, int flag, int hide_e)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i] && flag == -1)
	{
		j = 0;
		while (env[i][j] && env[i][j] == buf[j])
			j++;
		if (!buf[j] && env[i][j] == '=')
			flag = i;
	}
	if (flag == -1)
		return (ft_return(0, 0));
	i = flag;
	convert_flag(buf, env, i, hide_e);
	return (ft_return(1, 0));
}
