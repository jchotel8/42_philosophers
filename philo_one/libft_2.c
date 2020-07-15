/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:06:23 by jchotel           #+#    #+#             */
/*   Updated: 2020/04/20 17:31:04 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_atoi(const char *str)
{
	unsigned int	res;
	size_t			i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res * sign);
}

int	philoprintf(long int time, int id, char *str)
{
	ft_putstr(WHI);
	ft_putnbr(time);
	ft_putstr(" "RED);
	if (id >= 0)
		ft_putnbr(id);
	else
		ft_putstr("X");
	ft_putstr(" "YEL);
	ft_putstr(str);
	return (0);
}
