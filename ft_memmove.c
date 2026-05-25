/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:39:24 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/25 12:39:26 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write(unsigned char *dt, const unsigned char	*dtv, size_t n)
{
	size_t	i;

	i = 0;
	if (dt > dtv)
		{
			while (n > 0)
			{
				dt[n] = dtv[n];
				n--;
			}
		}
		else
		{
			while (i < n)
			{
				dt[i] = dtv[i];
				i++;
			}
		}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*dtv;

	if (!dest && !src)
		return (NULL);
	dt = (unsigned char *)dest;
	dtv = (const unsigned char *)src;
	ft_write(dt, dtv, n);
	return (dt);
}

#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "ABCDEFGH";

    // Copy "ABCDE" starting at index 0 to index 2
    // Resulting overlap: [A, B, A, B, C, D, E, H]
    memmove(str + 2, str, 5);

    printf("Result: %s\n", str); // Output: ABABCDEH
    return 0;
}
