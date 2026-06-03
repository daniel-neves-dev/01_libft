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

int main(void)
{
    test_substr();      printf("---------------------------------------\n\n");
    test_strjoin();     printf("---------------------------------------\n\n");
    printf("\033[34mPART 2 - ADDITIONAL CONSTRAINTS RUN COMPLETE.\033[0m\n");
    return (0);
}