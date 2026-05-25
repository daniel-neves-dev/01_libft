#include <stdio.h>
#include <string.h>

int main(void) {
    char destination[20] = "Hello, ";
    const char *source = "World!";
    size_t total_length;

    // sizeof(destination) provides the full buffer size (20)
    total_length = strlcat(destination, source, sizeof(destination));

    printf("Concatenated string: %s\n", destination); // "Hello, World!"
    printf("Resulting string length: %zu\n", strlen(destination));
    printf("Total length if space was unlimited: %zu\n", total_length);

    return (0);
}
