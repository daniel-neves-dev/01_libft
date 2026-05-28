/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:39:24 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/28 16:47:56 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*dtv;
	size_t				i;

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
