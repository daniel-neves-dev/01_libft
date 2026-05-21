/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:17:27 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/21 14:11:51 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	strlen;

	strlen = 0;
	while (*str)
	{
		strlen++;
		str++;
	}
	return (strlen);
}

#include <stdio.h>
int main() {
    char myStr[] = "Hello Daniel";

    printf("Length of string: %ld\n", ft_strlen(myStr));

    return 0;
}
