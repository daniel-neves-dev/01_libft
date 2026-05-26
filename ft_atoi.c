/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:14:02 by daniel            #+#    #+#             */
/*   Updated: 2026/05/26 12:14:05 by daniel           ###   ########.fr       */
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

#include <stdio.h>
int main() {
	char str1[] = "   -4256";
	char str2[] = "123apple";
	char str3[] = "blue321";
	char str4[] = "   ---4256";

	int num1 = atoi(str1);
	int num2 = atoi(str2);
	int num3 = atoi(str3);
	int num4 = atoi(str4);

	printf("String: '%s' -> Integer: %d\n", str1, num1);
	printf("String: '%s' -> Integer: %d\n", str2, num2);
	printf("String: '%s' -> Integer: %d\n", str3, num3);
	printf("String: '%s' -> Integer: %d\n", str4, num4);

	return 0;
}