#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include "libft.h"

// =============================================================================
// CORE TEST UNIT UTILITIES
// =============================================================================
void    print_result(const char *test_name, int test_num, int pass)
{
    if (pass)
        printf("  Test %02d [%s]: \033[32m[OK]\033[0m\n", test_num, test_name);
    else
        printf("  Test %02d [%s]: \033[31m[KO]\033[0m\n", test_num, test_name);
}

// =============================================================================
// MOULINETTE BEHAVIORAL TWIN EVALUATOR
// =============================================================================
void    eval_substr(const char *name, int num, const char *s, unsigned int start, size_t len)
{
    char *user_res = ft_substr(s, start, len);
    char *std_res = NULL;

    if (s)
    {
        size_t s_len = strlen(s);
        if (start >= s_len)
        {
            std_res = malloc(1);
            if (std_res) std_res[0] = '\0';
        }
        else
        {
            size_t available_len = s_len - start;
            size_t final_len = (len > available_len) ? available_len : len;
            std_res = malloc(final_len + 1);
            if (std_res)
            {
                strncpy(std_res, s + start, final_len);
                std_res[final_len] = '\0';
            }
        }
    }

    // Match verification checks
    int match = 0;
    if (!user_res && !std_res)
        match = 1;
    else if (user_res && std_res)
        match = (strcmp(user_res, std_res) == 0);

    print_result(name, num, match);

    if (user_res) free(user_res);
    if (std_res)  free(std_res);
}

void    eval_strjoin(const char *name, int num, const char *s1, const char *s2)
{
    char *user_res = ft_strjoin(s1, s2);
    char *std_res = NULL;

    if (s1 && s2)
    {
        std_res = malloc(strlen(s1) + strlen(s2) + 1);
        if (std_res)
        {
            strcpy(std_res, s1);
            strcat(std_res, s2);
        }
    }

    // Match verification checks
    int match = 0;
    if (!user_res && !std_res)
        match = 1;
    else if (user_res && std_res)
        match = (strcmp(user_res, std_res) == 0);

    print_result(name, num, match);

    if (user_res) free(user_res);
    if (std_res)  free(std_res);
}

void    eval_strtrim(const char *name, int num, const char *s1, const char *set)
{
    char *user_res = ft_strtrim(s1, set);
    char *std_res = NULL;

    // Strict 42 Behavioral simulation matching reference engine
    if (s1 && set)
    {
        size_t start = 0;
        size_t end = strlen(s1);

        while (s1[start] && strchr(set, s1[start]))
            start++;
        while (end > start && strchr(set, s1[end - 1]))
            end--;

        size_t trim_len = end - start;
        std_res = malloc(trim_len + 1);
        if (std_res)
        {
            strncpy(std_res, s1 + start, trim_len);
            std_res[trim_len] = '\0';
        }
    }

    // Match verification checks
    int match = 0;
    if (!user_res && !std_res)
        match = 1; // Both safely returned NULL on system limits
    else if (user_res && std_res)
    {
        match = (strcmp(user_res, std_res) == 0);
    }

    print_result(name, num, match);

    // Explicitly free pointers to ensure the evaluation engine leaves 0 leaks
    if (user_res)
        free(user_res);
    if (std_res)
        free(std_res);
}

void    eval_split(const char *name, int num, const char *s, char c)
{
    char **user_res = ft_split(s, c);
    char **std_res = NULL;

    // Behavioral twin baseline calculation
    if (s)
    {
        int words = 0;
        int i = 0;
        while (s[i])
        {
            while (s[i] && s[i] == c) i++;
            if (s[i] && s[i] != c)
            {
                words++;
                while (s[i] && s[i] != c) i++;
            }
        }
        std_res = malloc(sizeof(char *) * (words + 1));
        if (std_res)
        {
            int w = 0;
            i = 0;
            while (s[i])
            {
                while (s[i] && s[i] == c) i++;
                if (s[i] && s[i] != c)
                {
                    int len = 0;
                    while (s[i + len] && s[i + len] != c) len++;
                    std_res[w] = malloc(len + 1);
                    if (std_res[w])
                    {
                        strncpy(std_res[w], s + i, len);
                        std_res[w][len] = '\0';
                    }
                    w++;
                    i += len;
                }
            }
            std_res[w] = NULL;
        }
    }

    // Comprehensive Array Comparison Match Matrix
    int match = 1;
    if (!user_res && !std_res)
        match = 1;
    else if (!user_res || !std_res)
        match = 0;
    else
    {
        int idx = 0;
        while (user_res[idx] || std_res[idx])
        {
            if (!user_res[idx] || !std_res[idx] || strcmp(user_res[idx], std_res[idx]) != 0)
            {
                match = 0;
                break;
            }
            idx++;
        }
    }

    print_result(name, num, match);

    // Deep-Clean Memory Reclamation (Prevents Evaluation Engine Leaks)
    if (user_res)
    {
        int idx = 0;
        while (user_res[idx])
        {
            free(user_res[idx]);
            idx++;
        }
        free(user_res);
    }
    if (std_res)
    {
        int idx = 0;
        while (std_res[idx])
        {
            free(std_res[idx]);
            idx++;
        }
        free(std_res);
    }
}

void    eval_itoa(const char *name, int num, int n)
{
    char *user_res = ft_itoa(n);
    char *std_res = malloc(32); // Safe allocation cushion for 32-bit int string representation

    if (std_res)
    {
        // Generate system behavioral baseline using sprintf
        sprintf(std_res, "%d", n);
    }

    // Match verification checks
    int match = 0;
    if (!user_res && !std_res)
        match = 1;
    else if (user_res && std_res)
    {
        match = (strcmp(user_res, std_res) == 0);
    }

    print_result(name, num, match);

    if (user_res)
        free(user_res);
    if (std_res)
        free(std_res);
}

// =============================================================================
// ESPECIAL CASE FUNCTION APLLY FUNCTION
// =============================================================================

// Mock function 1: Increments character ASCII value by 1 (ignoring index)
char mock_toupper_slide(unsigned int i, char c)
{
    (void)i;
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

// Mock function 2: Encodes the character based entirely on its index position
char mock_index_shift(unsigned int i, char c)
{
    return (c + (i % 3));
}

void    eval_strmapi(const char *name, int num, const char *s, char (*f)(unsigned int, char))
{
    char *user_res = ft_strmapi(s, f);
    char *std_res = NULL;

    // Strict 42 Behavioral simulation matching reference engine
    if (s && f)
    {
        size_t len = strlen(s);
        std_res = malloc(len + 1);
        if (std_res)
        {
            unsigned int i = 0;
            while (s[i])
            {
                std_res[i] = f(i, s[i]);
                i++;
            }
            std_res[i] = '\0';
        }
    }

    // Match verification checks
    int match = 0;
    if (!user_res && !std_res)
        match = 1;
    else if (user_res && std_res)
    {
        match = (strcmp(user_res, std_res) == 0);
    }

    print_result(name, num, match);

    if (user_res)
        free(user_res);
    if (std_res)
        free(std_res);
}

// Mock function 1: Modifies character to uppercase in-place (ignoring index)
void mock_iter_toupper(unsigned int i, char *c)
{
    (void)i;
    if (*c >= 'a' && *c <= 'z')
        *c -= 32;
}

// Mock function 2: Shifts character value based on its index position in-place
void mock_iter_index_shift(unsigned int i, char *c)
{
    *c = *c + (i % 3);
}

void    eval_striteri(const char *name, int num, const char *s, void (*f)(unsigned int, char*))
{
    char *user_buf = NULL;
    char *std_buf = NULL;
    int match = 0;

    if (s)
    {
        user_buf = strdup(s);
        std_buf = strdup(s);
    }

    if (user_buf && std_buf && f)
    {
        // Run your library in-place modification function
        ft_striteri(user_buf, f);

        // Run baseline behavioral twin simulation loop
        unsigned int i = 0;
        while (std_buf[i])
        {
            f(i, &std_buf[i]);
            i++;
        }

        match = (strcmp(user_buf, std_buf) == 0);
    }
    else if (!s)
    {
        // Safe protection boundary testing for NULL strings if function handles it
        ft_striteri(NULL, f);
        match = 1;
    }

    print_result(name, num, match);

    if (user_buf) free(user_buf);
    if (std_buf)  free(std_buf);
}

// =============================================================================
// TEST SUITE SUITES
// =============================================================================
void    eval_putchar_fd(const char *name, int num, char c)
{
    int     pipe_fds[2];
    char    read_buf = 0;
    int     match = 0;

    // Open a system pipe ([0] is read end, [1] is write end)
    if (pipe(pipe_fds) == 0)
    {
        // Run your library function writing to the pipe's input channel
        ft_putchar_fd(c, pipe_fds[1]);

        // Close the write end immediately so read doesn't block infinitely
        close(pipe_fds[1]);

        // Read the intercepted character back out of the pipe's output channel
        ssize_t bytes_read = read(pipe_fds[0], &read_buf, 1);

        // Verify exactly 1 byte was read and it matches the input character
        if (bytes_read == 1 && read_buf == c)
            match = 1;

        // Clean up the remaining file descriptor handle
        close(pipe_fds[0]);
    }

    print_result(name, num, match);
}


void test_substr(void)
{
    printf("--- TESTING ft_substr ---\n");
    const char *str = "The 42 school foundation!";

    // MEDIUM LEVEL
    eval_substr("Extract word from the beginning", 1, str, 0, 3);
    eval_substr("Extract word from the middle", 2, str, 7, 6);
    eval_substr("Extract trailing punctuation character", 3, str, 24, 1);
    eval_substr("Length spans precisely to the exact string end", 4, str, 13, 12);
    eval_substr("Request single character extract token", 5, str, 4, 1);

    // HARD LEVEL
    eval_substr("Start index value out of bounds completely", 6, str, 50, 5);
    eval_substr("Start index matches exactly string length", 7, str, 25, 5);
    eval_substr("Requested len size overflows remaining bounds", 8, str, 13, 500);
    eval_substr("Extract inside a completely empty string \"\"", 9, "", 0, 10);
    eval_substr("Vastly oversized len capacity parameter boundary limit", 10, str, 4, SIZE_MAX);
}

void test_strjoin(void)
{
    printf("--- TESTING ft_strjoin ---\n");

    // MEDIUM LEVEL
    eval_strjoin("Standard join of two words", 1, "Hello ", "World!");
    eval_strjoin("Join number sequence to text", 2, "Error code: ", "42");
    eval_strjoin("Join single characters together", 3, "a", "b");
    eval_strjoin("Join prefix space padding", 4, "   ", "Trimmed?");
    eval_strjoin("Join trailing symbols sequence", 5, "Database status", " [OK]");

    // HARD LEVEL
    eval_strjoin("First string parameter is empty \"\"", 6, "", "Valid suffix");
    eval_strjoin("Second string parameter is empty \"\"", 7, "Valid prefix", "");
    eval_strjoin("Both string parameters are empty \"\"", 8, "", "");

    char block_5k[5001];
    memset(block_5k, 'm', 5000); block_5k[5000] = '\0';
    eval_strjoin("Massive 5000 byte concatenation window", 9, block_5k, "END");
    eval_strjoin("Join long special escape character chains", 10, "\n\t\r", "\v\f\0");
}

void test_strtrim(void)
{
    printf("--- TESTING ft_strtrim ---\n");

    // MEDIUM LEVEL
    eval_strtrim("Trim spaces from both ends", 1, "   Hello World   ", " ");
    eval_strtrim("Trim specific letters from start and end", 2, "xaHello Worldax", "ax");
    eval_strtrim("Trim characters only present at the start", 3, "777Hello", "7");
    eval_strtrim("Trim characters only present at the end", 4, "World!!!", "!");
    eval_strtrim("No trim matches found anywhere", 5, "Hello World", "xyz");

    // HARD LEVEL (Triggers extreme trimming allocations)
    eval_strtrim("Entire string consists of trim set characters", 6, "bbbbbbbb", "b");
    eval_strtrim("Trim set characters alternate throughout", 7, "  \t  \t  ", " \t");
    eval_strtrim("Set parameter is an empty string \"\"", 8, "Hello World", "");
    eval_strtrim("S1 parameter is an empty string \"\"", 9, "", "abc");
    eval_strtrim("Both parameters are empty strings \"\"", 10, "", "");
}

void test_split(void)
{
    printf("--- TESTING ft_split ---\n");

    // MEDIUM LEVEL
    eval_split("Standard sentence broken by spaces", 1, "The 42 school foundation", ' ');
    eval_split("Path segments split by forward slash", 2, "bin/usr/local/include", '/');
    eval_split("Single character text token check", 3, "a", ' ');
    eval_split("String containing words but no delimiters", 4, "Hello", 'z');
    eval_split("Delimiter matches first and last character", 5, "-word-", '-');

    // HARD LEVEL (Triggers nested edge-case allocations)
    eval_split("Consecutive repeating delimiters block", 6, "Hello------World!!!", '-');
    eval_split("String consisting entirely of delimiters", 7, "xxxxxxx", 'x');
    eval_split("Empty string parameter argument \"\"", 8, "", 'c');
    eval_split("String with extended ASCII character splits", 9, "split\200word\200test", '\200');
    eval_split("Delimiter parameter character set to null terminator", 10, "Hello World", '\0');
}

void test_itoa(void)
{
    printf("--- TESTING ft_itoa ---\n");

    // MEDIUM LEVEL
    eval_itoa("Standard positive single digit", 1, 7);
    eval_itoa("Standard positive multi-digit number", 2, 1337);
    eval_itoa("Standard negative multi-digit number", 3, -4242);
    eval_itoa("The absolute neutral zero point", 4, 0);
    eval_itoa("Large positive integer value block", 5, 100003);

    // HARD LEVEL (Triggers extreme boundary allocations)
    eval_itoa("Exact positive ceiling value matching INT_MAX", 6, INT_MAX);
    eval_itoa("Exact negative floor value matching INT_MIN (The Trap)", 7, INT_MIN);
    eval_itoa("Small negative value threshold edge", 8, -1);
    eval_itoa("Large scale round multi-zero layout", 9, 2000000000);
    eval_itoa("Large scale round negative multi-zero layout", 10, -2000000000);
}

void test_strmapi(void)
{
    printf("--- TESTING ft_strmapi ---\n");

    // MEDIUM LEVEL (Using character slider mock)
    eval_strmapi("Map all lowercase to uppercase", 1, "hello", mock_toupper_slide);
    eval_strmapi("Map mixed alpha values together", 2, "42School", mock_toupper_slide);
    eval_strmapi("Map single isolated token character", 3, "z", mock_toupper_slide);
    eval_strmapi("Map spaces and punctuation sequences", 4, "a b!c", mock_toupper_slide);
    eval_strmapi("Map a clean numeric string layout", 5, "12345", mock_toupper_slide);

    // HARD LEVEL (Testing index positions and edge arguments)
    eval_strmapi("Index shift transformation logic test", 6, "aaaaa", mock_index_shift);
    eval_strmapi("Index shift on larger mixed sentence layout", 7, "The 42 Project", mock_index_shift);
    eval_strmapi("Map inside an empty string component \"\"", 8, "", mock_toupper_slide);
    eval_strmapi("Index shift inside empty string layout", 9, "", mock_index_shift);

    char block_5k[5001];
    memset(block_5k, 'a', 5000); block_5k[5000] = '\0';
    eval_strmapi("Massive 5000 item string transformation array", 10, block_5k, mock_index_shift);
}

void test_striteri(void)
{
    printf("--- TESTING ft_striteri ---\n");

    // MEDIUM LEVEL (Using in-place toupper mock)
    eval_striteri("Iterate lowercase to uppercase in-place", 1, "hello", mock_iter_toupper);
    eval_striteri("Iterate mixed strings with numerical values", 2, "42Norminette", mock_iter_toupper);
    eval_striteri("Iterate a single token isolated character", 3, "q", mock_iter_toupper);
    eval_striteri("Iterate sentence padding with space structures", 4, "x y ! z", mock_iter_toupper);
    eval_striteri("Iterate string with non-alpha numbers", 5, "98765", mock_iter_toupper);

    // HARD LEVEL (Testing index references and empty parameters)
    eval_striteri("In-place index transformation mapping calculation", 6, "ccccc", mock_iter_index_shift);
    eval_striteri("In-place index shift on longer sentences", 7, "The 42 Network", mock_iter_index_shift);
    eval_striteri("Iterate inside an empty string component \"\"", 8, "", mock_iter_toupper);
    eval_striteri("In-place index shift inside empty string", 9, "", mock_iter_index_shift);

    char block_5k[5001];
    memset(block_5k, 'b', 5000); block_5k[5000] = '\0';
    eval_striteri("Massive 5000 item string block traversal check", 10, block_5k, mock_iter_index_shift);
}

void test_putchar_fd(void)
{
    printf("--- TESTING ft_putchar_fd ---\n");

    // MEDIUM LEVEL
    eval_putchar_fd("Write standard lowercase character 'a'", 1, 'a');
    eval_putchar_fd("Write standard uppercase character 'Z'", 2, 'Z');
    eval_putchar_fd("Write a standard numeric character '5'", 3, '5');
    eval_putchar_fd("Write a standard space spacing character", 4, ' ');
    eval_putchar_fd("Write a basic punctuation punctuation mark '*'", 5, '*');

    // HARD LEVEL (Testing control characters and boundary conditions)
    eval_putchar_fd("Write a null terminator literal character \\0", 6, '\0');
    eval_putchar_fd("Write a newline escape control character \\n", 7, '\n');
    eval_putchar_fd("Write a horizontal tab escape character \\t", 8, '\t');
    eval_putchar_fd("Write an extended ASCII boundary byte (128)", 9, (char)128);
    eval_putchar_fd("Write an alternative high boundary byte (255)", 10, (char)255);
}

int main(void)
{
    test_substr();      printf("---------------------------------------\n\n");
    test_strjoin();     printf("---------------------------------------\n\n");
    test_strtrim();     printf("---------------------------------------\n\n");
    test_split();       printf("---------------------------------------\n\n");
    test_itoa();        printf("---------------------------------------\n\n");
    test_strmapi();     printf("---------------------------------------\n\n");
    test_striteri();    printf("---------------------------------------\n\n");
    test_putchar_fd();  printf("---------------------------------------\n\n");

    printf("\033[34mPART 2 - ADDITIONAL CONSTRAINTS RUN COMPLETE.\033[0m\n");
    return (0);
}