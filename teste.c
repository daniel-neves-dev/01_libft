#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello World!";

    // Shift "World!" left by 6 spaces to overwrite "Hello "
    // Source: &str[6] ("World!")
    // Destination: &str[0]
    // Bytes: 7 (includes the null terminator '\0')
    memmove(str, str + 6, 7);

    printf("%s\n", str); // Output: World!
    return 0;
}
