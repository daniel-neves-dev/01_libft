#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
// MOULINETTE LINKED LIST EVALUATOR
// =============================================================================
void    eval_lstnew(const char *name, int num, void *expected_content, size_t data_size)
{
    // Execute your library function
    t_list *user_node = ft_lstnew(expected_content);
    int match = 0;

    if (!user_node)
    {
        // Fail if allocation returned NULL unexpectedly
        match = 0;
    }
    else
    {
        // 1. Verify next pointer is explicitly initialized to NULL
        int next_is_null = (user_node->next == NULL);

        // 2. Verify content binding address matches or data matches integrity
        int content_matches = 0;
        if (expected_content == NULL && user_node->content == NULL)
        {
            content_matches = 1;
        }
        else if (expected_content && user_node->content)
        {
            if (data_size > 0)
                content_matches = (memcmp(user_node->content, expected_content, data_size) == 0);
            else
                content_matches = (user_node->content == expected_content);
        }

        if (next_is_null && content_matches)
            match = 1;
    }

    print_result(name, num, match);

    // Free the wrapper allocation node structure to guarantee 0 framework leaks
    if (user_node)
        free(user_node);
}

// =============================================================================
// TEST SUITE SUITES
// =============================================================================
void test_lstnew(void)
{
    printf("\n--- TESTING ft_lstnew ---\n");

    // Static variables to pass safely by reference
    static int   num_fortytwo = 42;
    static int   num_negative = -1337;
    static char  char_token = 'A';

    // MEDIUM LEVEL (Testing standard data types)
    eval_lstnew("Initialize node with static string payload", 1, "Hello World", 0);
    eval_lstnew("Initialize node with positive integer payload", 2, &num_fortytwo, sizeof(int));
    eval_lstnew("Initialize node with negative integer payload", 3, &num_negative, sizeof(int));
    eval_lstnew("Initialize node with single character literal", 4, &char_token, sizeof(char));

    char *dup_str = strdup("Dynamic Allocation String");
    eval_lstnew("Initialize node with pre-allocated heap string", 5, dup_str, 0);

    // HARD LEVEL (Testing extreme conditions, structures, and empty pointers)
    // 42 Edge Case: Content pointer is explicitly NULL
    eval_lstnew("Initialize node with absolute NULL pointer content", 6, NULL, 0);

    // Testing layout mapping complex structures
    struct s_mock_box { int x; char y; double z; } box = {10, 'b', 3.1415};
    eval_lstnew("Initialize node mapping an entire data structure", 7, &box, sizeof(struct s_mock_box));

    eval_lstnew("Initialize node with empty string literal \"\"", 8, "", 1);

    static unsigned long large_val = ULONG_MAX;
    eval_lstnew("Initialize node with massive unsigned limit storage", 9, &large_val, sizeof(unsigned long));

    // Array referencing
    int int_array[5] = {1, 2, 3, 4, 5};
    eval_lstnew("Initialize node pointing to sequential array element address", 10, int_array, sizeof(int_array));

    // Clean up our dynamic medium test variable helper
    free(dup_str);
}

int main(void)
{
    test_lstnew();      printf("---------------------------------------\n\n");

    printf("\033[34mPART 3 - LINKED LIST CONSTRAINTS RUN COMPLETE.\033[0m\n");
    return (0);
}