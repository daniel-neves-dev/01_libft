/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:14:02 by daniel            #+#    #+#             */
/*   Updated: 2026/05/27 09:34:18 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int sign;

	result = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
	{
		nptr++;
	}
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign -= 1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}
