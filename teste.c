#include <stdio.h>
#include <string.h>
#include "libft.h"
size_t	ft_strlcat(char *dest, const char *src, size_t size);

int main(void) {
	// Buffer com espaço de sobra (tamanho 20)
	char destino[20] = "Ola ";
	char origem[] = "Mundo!";
	size_t total_tentado;

	// Tentando concatenar
	total_tentado = ft_strlcat(destino, origem, sizeof(destino));

	printf("Resultado: %s\n", destino); // Imprime: Ola Mundo!
	printf("Tamanho retornado: %zu\n", total_tentado); // 4 (Ola ) + 6 (Mundo!) = 10
	printf("Tamanho do buffer: %zu\n", sizeof(destino)); // 20

	// Como 10 < 20, sabemos que coube tudo perfeitamente!

	char destino_pequeno[8] = "Ola "; // Buffer bem apertado
	size_t ret = ft_strlcat(destino_pequeno, "Mundo!", sizeof(destino_pequeno));

	printf("Resultado: %s\n", destino_pequeno); // Imprime: Ola Mun
	printf("Retorno: %zu\n", ret); // Retorna 10 (4 de "Ola " + 6 de "Mundo!")

	if (ret >= sizeof(destino_pequeno)) {
		printf("Aviso: A string foi truncada!\n");
		return 0;
	}
}