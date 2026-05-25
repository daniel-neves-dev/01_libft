/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:39:24 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/25 11:01:45 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	unsigned char *dt;
	const unsigned char *dtv;

	dt = dest;
	dtv = src;
	i = 0;
	if (!dt && !dtv)
		return (NULL);
	while (i < n)
	{
		dt[i] = dtv[i];
		i++;
	}
	return (dt);
}
