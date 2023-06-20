/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:48 by agrun             #+#    #+#             */
/*   Updated: 2023/06/05 10:30:53 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	free.c: 1.	*/

int	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		(ft_return(1, 0));
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
	return (ft_return(1, 0));
}

/*	free.c: 2.	*/

int	ft_free(char **str)
{
	if (!*str)
		return (ft_return(0, 0));
	free(*str);
	*str = NULL;
	return (ft_return(1, 0));
}
