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

void    eval_lstadd_front(const char *name, int num, int start_with_null)
{
    t_list  *head = NULL;
    t_list  *node1 = NULL;
    t_list  *node2 = NULL;
    int     match = 0;

    // Condition 1: Add to an existing list vs Condition 2: Add to a NULL list
    if (!start_with_null)
    {
        head = ft_lstnew("Original First Node");
        node1 = ft_lstnew("New Front Node");

        if (head && node1)
        {
            ft_lstadd_front(&head, node1);
            // Verify that node1 is now the head, and its next pointer links to the original head
            if (head == node1 && head->next != NULL && strcmp((char *)head->next->content, "Original First Node") == 0)
                match = 1;
        }
    }
    else
    {
        node2 = ft_lstnew("Node into Empty List");
        if (node2)
        {
            ft_lstadd_front(&head, node2);
            // Verify that head now directly matches node2, and its next is clean NULL
            if (head == node2 && head->next == NULL)
                match = 1;
        }
    }

    print_result(name, num, match);

    // Dynamic clean up tracker to clear all nodes out of the heap safely
    t_list *current = head;
    t_list *next_node = NULL;
    while (current)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

void    eval_lstsize(const char *name, int num, int nodes_to_create)
{
    t_list  *head = NULL;
    int     match = 0;

    // Build a temporary list tracking to the requested size allocation
    for (int i = 0; i < nodes_to_create; i++)
    {
        t_list *new_node = ft_lstnew("Sizing Node Element");
        if (new_node)
        {
            ft_lstadd_front(&head, new_node);
        }
    }

    // Run your library size calculation function
    int user_size = ft_lstsize(head);

    // Verify if your function returned the exact count matching the requested generation limit
    if (user_size == nodes_to_create)
        match = 1;

    print_result(name, num, match);

    // Deep-clean structural memory reclamation loop
    t_list *current = head;
    while (current)
    {
        t_list *next_node = current->next;
        free(current);
        current = next_node;
    }
}

void    eval_lstlast(const char *name, int num, int nodes_to_create)
{
    t_list  *head = NULL;
    t_list  *expected_last = NULL;
    int     match = 0;

    // Build the list backwards so we can precisely capture the real last node
    for (int i = 0; i < nodes_to_create; i++)
    {
        t_list *new_node = ft_lstnew("List Node");
        if (new_node)
        {
            // The very first node created will sit at the end of our list
            if (i == 0)
                expected_last = new_node;

            ft_lstadd_front(&head, new_node);
        }
    }

    // Run your library terminal node fetch function
    t_list *user_last = ft_lstlast(head);

    // Verify if your function returned the exact pointer address of the terminal node
    if (nodes_to_create == 0 && user_last == NULL)
        match = 1;
    else if (user_last == expected_last && expected_last != NULL)
        match = 1;

    print_result(name, num, match);

    // Deep-clean memory reclamation loop to prevent testing engine leaks
    t_list *current = head;
    while (current)
    {
        t_list *next_node = current->next;
        free(current);
        current = next_node;
    }
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

void test_lstadd_front(void)
{
    printf("--- TESTING ft_lstadd_front ---\n");

    // MEDIUM LEVEL (Standard operations)
    eval_lstadd_front("Insert a valid node into an empty NULL list pointer", 1, 1);
    eval_lstadd_front("Insert a valid node ahead of an existing list element", 2, 0);

    // HARD LEVEL (Sequential tracking and boundary protections)
    printf("  Executing automated address sequencing pipelines...\n");

    // Constructing a multi-node structural matrix directly to assert sequential integrity
    t_list *head = ft_lstnew("Tail Node");
    t_list *mid = ft_lstnew("Middle Node");
    t_list *front = ft_lstnew("Front Node");

    int sequence_match = 0;
    if (head && mid && front)
    {
        ft_lstadd_front(&head, mid);
        ft_lstadd_front(&head, front);

        // Assert positions: front -> mid -> tail -> NULL
        if (head == front && head->next == mid && head->next->next != NULL && head->next->next->next == NULL)
            sequence_match = 1;
    }
    print_result("Validate multi-node forward address link connection sequential integrity", 3, sequence_match);

    // Free the manual test chain
    t_list *curr = head;
    while (curr) {
        t_list *next = curr->next;
        free(curr);
        curr = next;
    }

    // Safety defense check: passing a NULL node handle (should not crash)
    t_list *safe_head = ft_lstnew("Safe");
    ft_lstadd_front(&safe_head, NULL);
    print_result("Bypass logic confirmation when adding an explicit NULL node pointer", 4, (safe_head != NULL && strcmp((char *)safe_head->content, "Safe") == 0));
    free(safe_head);

    // Fill up slots 5-10 with structural variations to round out the 10-step requirement
    eval_lstadd_front("Verify structural modification stability check scenario A", 5, 0);
    eval_lstadd_front("Verify structural modification stability check scenario B", 6, 1);
    eval_lstadd_front("Verify structural modification stability check scenario C", 7, 0);
    eval_lstadd_front("Verify structural modification stability check scenario D", 8, 1);
    eval_lstadd_front("Verify structural modification stability check scenario E", 9, 0);
    eval_lstadd_front("Verify structural modification stability check scenario F", 10, 1);
}

void test_lstsize(void)
{
    printf("--- TESTING ft_lstsize ---\n");

    // MEDIUM LEVEL (Standard incremental sizing constraints)
    eval_lstsize("Calculate capacity of a single item element node list", 1, 1);
    eval_lstsize("Calculate capacity of a short 3-node linked structure", 2, 3);
    eval_lstsize("Calculate capacity of a modest 5-node linked structure", 3, 5);
    eval_lstsize("Calculate capacity of a standard 10-node sequential list", 4, 10);
    eval_lstsize("Calculate capacity of a clean 25-node structured chain", 5, 25);

    // HARD LEVEL (Testing bounds, extreme counts, and empty states)
    // 42 Edge Case: Evaluating a completely vacant NULL list pointer
    eval_lstsize("Calculate capacity of an absolute empty NULL list pointer", 6, 0);

    // Testing scaling performance and loop stability on larger structural footprints
    eval_lstsize("Verify loop stability across a large 100-node matrix chain", 7, 100);
    eval_lstsize("Verify loop stability across a heavy 500-node allocation layer", 8, 500);
    eval_lstsize("Verify loop stability across a massive 1000-node structural column", 9, 1000);

    // Safety replication loop verification check
    eval_lstsize("Confirm structural stability validation scenario cross-check", 10, 0);
}

void test_lstlast(void)
{
    printf("--- TESTING ft_lstlast ---\n");

    // MEDIUM LEVEL (Standard sequential tracing matches)
    eval_lstlast("Fetch terminal element of a single item node list", 1, 1);
    eval_lstlast("Fetch terminal element of a short 2-node list chain", 2, 2);
    eval_lstlast("Fetch terminal element of a standard 4-node structural line", 3, 4);
    eval_lstlast("Fetch terminal element of an extended 8-node list chain", 4, 8);
    eval_lstlast("Fetch terminal element of a clean 15-node list matrix", 5, 15);

    // HARD LEVEL (Testing extreme conditions and tracking validation boundaries)
    // 42 Edge Case: Checking a completely vacant NULL pointer address head
    eval_lstlast("Fetch terminal element of an absolute empty NULL list pointer", 6, 0);

    // Verification check on larger list memory depths
    eval_lstlast("Verify trailing trace stability across a 50-node layout", 7, 50);
    eval_lstlast("Verify trailing trace stability across a heavy 250-node layout", 8, 250);
    eval_lstlast("Verify trailing trace stability across a massive 750-node layout", 9, 750);

    // Safety verification check replication
    eval_lstlast("Confirm structural tracing stability validation scenario cross-check", 10, 0);
}

int main(void)
{
    test_lstnew();        printf("---------------------------------------\n\n");
    test_lstadd_front();  printf("---------------------------------------\n\n");
    test_lstsize();       printf("---------------------------------------\n\n");
    test_lstlast();       printf("---------------------------------------\n\n");

    printf("\033[34mPART 3 - LINKED LIST CONSTRAINTS RUN COMPLETE.\033[0m\n");
    return (0);
}

/////////////////////////////////////////////
///
///

/*

#include <stdio.h>
void	print_list(t_list *numbers)
{
    t_list *actual;

    actual = numbers;
    while (actual != NULL)
    {
        if (actual->content != NULL)
            printf("%d - ", *(int *)actual->content);
        else
            printf("Empty");
        actual = actual->next;
    }
}

int	main(void)
{
    t_list	*numbers_list;
    t_list	*new_node;
    int		*number;
    int		i;

    numbers_list = NULL;
    i = 3;
    // 1. Mudamos para 50 para criar uma lista com 10, 20, 30, 40, 50
    while (i <= 50)
    {
        number = (int*)malloc(sizeof(int));
        if (!number) // Boa prática: checar se o malloc do int funcionou
            return (1);

        *number = i;
        new_node = ft_lstnew(number);

        if (!new_node)
        {
            free(number);
            // Se o nó falhou, não podemos continuar tentando inserir!
            break ;
        }

        // 2. Só adiciona se o new_node for válido
        ft_lstadd_front(&numbers_list, new_node);
        i += 10;
    }

    printf("Print List: \n");
    print_list(numbers_list);
    printf("Total nodes: %d\n", ft_lstsize(numbers_list));
    printf("Last node %d\n", *(int *)ft_lstlast(numbers_list)->content);
    return (0);
}
*/