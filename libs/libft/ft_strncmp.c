/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:34:14 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/21 14:56:19 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	int	index;

	index = 0;
	while (s1[index] && (s1[index] == s2[index]) &&
	(unsigned int)index < n - 1)
		index++;
	if (n == 0)
		return (0);
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
