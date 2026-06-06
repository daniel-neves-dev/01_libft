/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 10:20:17 by dneves-d          #+#    #+#             */
/*   Updated: 2026/06/06 10:20:22 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t	count_words;
	int		nw;

	nw = 1;
	count_words = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (nw)
			{
				count_words++;
				nw = 0;
			}
		}
		else
			nw = 1;
		s++;
	}
	return (count_words);
}

char	**ft_free_split(char **split, size_t j)
{
	while (j > 0)
	{
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

size_t	ft_len_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		split[j] = ft_substr(s, i, ft_len_word(&s[i], c));
		if (!split[j])
			return (ft_free_split(split, j));
		i += ft_len_word(&s[i], c);
		j++;
	}
	split[j] = NULL;
	return (split);
}
