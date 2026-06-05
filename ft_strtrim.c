/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:31:12 by dneves-d          #+#    #+#             */
/*   Updated: 2026/06/04 17:31:15 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len_s1;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return ft_strdup("");
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return ft_strdup("");
	len_s1 = end - start + 1;
	return (ft_substr(s1, start, len_s1));
}

/*
#include <stdlib.h>
int main(void)
{
	// Cenário 1: Caso clássico (Espaços em branco nas pontas)
	char const *frase1 = "   Olá, 42 São Paulo!   ";
	char const *set1 = " ";
	char *resultado1 = ft_strtrim(frase1, set1);

	printf("--- Teste 1: Trim de Espaços ---\n");
	printf("Original:  \"%s\"\n", frase1);
	printf("Resultado: \"%s\"\n\n", resultado1);
	free(resultado1); // Liberação obrigatória do malloc interno

	// Cenário 2: Símbolos misturados (Ordem no 'set' não importa)
	char const *frase2 = "混沌!#@...Olá Mundo...@#!混沌x";
	char const *set2 = "x.!@#混沌";
	char *resultado2 = ft_strtrim(frase2, set2);

	printf("--- Teste 2: Símbolos e Caracteres Especiais ---\n");
	printf("Original:  \"%s\"\n", frase2);
	printf("Resultado: \"%s\"\n\n", resultado2);
	free(resultado2);

	// Cenário 3: Caso extremo (A string inteira é feita de caracteres do set)
	char const *frase3 = "xxxxx";
	char const *set3 = "x";
	char *resultado3 = ft_strtrim(frase3, set3);

	printf("--- Teste 3: String Totalmente Aparada ---\n");
	printf("Original:  \"%s\"\n", frase3);
	// Deve exibir uma string vazia "" sem quebrar o programa
	printf("Resultado: \"%s\"\n\n", resultado3);
	free(resultado3);

	return (0);
}*/