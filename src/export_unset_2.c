/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_2.c	                	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	export_unset_2.c: 1.	*/

int	ft_array_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (ft_return(i, 0));
}

/*	export_unset_2.c: 2.	*/
/*	Making sure that the new dimensional array is smaller by one string.
	It is mandatory to malloc every substring before copying the content.	*/

static char	**rem_env_str(char **env, int flag, int i, int j)
{
	char	**new;

	i = ft_array_len(env);
	new = malloc(sizeof(char *) * (i));
	if (!new)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (i != flag)
		{
			new[j] = add_env_str(env, i, 0);
			if (!new[j])
			{
				ft_free_array(new);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}

/*	export_unset_2.c: 3.	*/

char	**rem_env(char **env, char *ref)
{
	int		i;
	int		j;
	int		flag;
	char	**new;

	i = 0;
	j = 0;
	flag = -1;
	while (env[i] && flag < 0)
	{
		while (env[i][j] == ref[j])
			j++;
		if (!ref[j])
			flag = i;
		j = 0;
		i++;
	}
	if (flag < 0)
		return (env);
	new = rem_env_str(env, flag, 0, 0);
	if (!new)
		return (NULL);
	return (new);
}

/*	export_unset_2.c: 4.	*/
/*	This function is used at the start of minishell, it creates a custo-
	mizable copy of the envp-array which is vital for all shell commands.	*/

char	**copy_env(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = add_new_str(envp[i], 0, 0);
		if (!new[i])
		{
			write (2, "Error\nMalloc failed.\n", 21);
			ft_free_array(new);
			return (NULL);
		}
		i++;
	}
	new[i] = 0;
	return (new);
}

/*	export_unset_2.c: 5.	*/
/*	If there is no line on the env array corresponding to the prompt
	given by unset it's supposed to do nothing.

	If the mode variable is at 1, consider only the content up to the
	"="-sign and disregard the rest.				*/

int	check_valid_export_unset(char **env, char *ref, int i, int mode)
{
	int	flag;
	int	j;

	flag = -1;
	while (env[i] && flag < 0)
	{
		j = 0;
		while (!mode && env[i][j] == ref[j])
			j++;
		if (!mode && !ref[j])
			flag = i;
		while (mode && env[i][j] == ref[j] && ref[j] != '=')
			j++;
		if (mode && ref[j] == '=')
			flag = i;
		i++;
	}
	if (flag != -1)
		return (ft_return(1, 0));
	return (ft_return(0, 0));
}
