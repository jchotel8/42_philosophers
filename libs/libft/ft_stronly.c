/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stronly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:34:19 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/21 14:56:19 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_stronly(const char *s, const char *s2)
{
	int index;

	index = 0;
	while (s2[index])
	{
		if (!ft_strchr(s, s2[index]))
			return (0);
		index++;
	}
	return (1);
}
