/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:45:59 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/25 14:57:23 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

#include <stdio.h>
int main() {
    char lower = 'g';
    char upper = ft_toupper(lower);

    printf("Original: %c\n", lower); // Outputs: g
    printf("Uppercase: %c\n", upper); // Outputs: G

    // Passing a non-lowercase character
    printf("Non-letter: %c\n", ft_toupper('5')); // Outputs: 5 (unchanged)

    return 0;
}
