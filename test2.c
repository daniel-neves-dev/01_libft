#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
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

    // Strict 42 Behavioral simulation matching reference engine
    if (s)
    {
        size_t s_len = strlen(s);
        if (start >= s_len)
        {
            std_res = malloc(1);
            if (std_res)
                std_res[0] = '\0';
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

    // Validation matching
    int match = 0;
    if (!user_res && !std_res)
        match = 1; // Both failed safely on malloc exhaustion simulation
    else if (user_res && std_res)
    {
        match = (strcmp(user_res, std_res) == 0);
    }

    print_result(name, num, match);

    // Dynamic heap allocation cleanup loop
    if (user_res)
        free(user_res);
    if (std_res)
        free(std_res);
}

// =============================================================================
// TEST SUITE SUITES
// =============================================================================
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
    // 42 Edge Case: start index completely outside string dimensions
    eval_substr("Start index value out of bounds completely", 6, str, 50, 5);
    eval_substr("Start index matches exactly string length", 7, str, 25, 5);

    // 42 Edge Case: len capacity value is vastly oversized
    eval_substr("Requested len size overflows remaining bounds", 8, str, 13, 500);

    eval_substr("Extract inside a completely empty string \"\"", 9, "", 0, 10);
    eval_substr("Vastly oversized len capacity parameter boundary limit", 10, str, 4, SIZE_MAX);
}

int main(void)
{
    test_substr();
    printf("---------------------------------------\n\n");
    printf("\033[34mPART 2 - ADDITIONAL CONSTRAINTS RUN COMPLETE.\033[0m\n");
    return (0);
}