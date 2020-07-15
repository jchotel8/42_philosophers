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

#include "philo_three.h"
#include <stdarg.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *a;

	a = s;
	while (n-- > 0)
		*a++ = c;
	return (s);
}

void	*ft_calloc(size_t n, size_t size)
{
	void *new;

	if (!(new = (void *)malloc(size * n)))
		return (0);
	ft_memset(new, 0, size * n);
	return ((void *)new);
}

int		ft_atoi(const char *str)
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

char	*ft_itoa_philo(int i)
{
	long	n;
	int		c;
	char	*s;

	c = i < 0;
	n = c ? -(long)i : i;
	while (i /= 10)
		c++;
	s = ft_calloc(c + 2, sizeof(int));
	*s = '/';
	while ((s[c + 1] = n % 10 + '0') && (n /= 10))
		c--;
	return (s);
}

int		philoprintf(long int time, int id, char *str)
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
