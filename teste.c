#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void    eval_strlcat(const char *test_name, int test_num, const char *initial_dest, const char *src, size_t size, size_t buffer_size)
{
    char    *user_dest = malloc(buffer_size);
    char    *std_dest = malloc(buffer_size);

    // Initialize buffers identically with the starting string and pad leftovers with guard bytes
    memset(user_dest, 'A', buffer_size);
    memset(std_dest, 'A', buffer_size);
    strcpy(user_dest, initial_dest);
    strcpy(std_dest, initial_dest);

    // Call your implementation
    size_t user_ret = strlcat(user_dest, src, size);

    // Explicit behavioral twin of standard strlcat (handles Linux/macOS cross-compatibility)
    size_t dest_len = strlen(std_dest);
    size_t src_len = strlen(src);
    size_t std_ret;

    if (size <= dest_len)
        std_ret = size + src_len;
    else
    {
        std_ret = dest_len + src_len;
        size_t copy_len = size - dest_len - 1;
        if (src_len < copy_len)
            copy_len = src_len;
        memcpy(std_dest + dest_len, src, copy_len);
        std_dest[dest_len + copy_len] = '\0';
    }

    // 1. Check if the return values match perfectly
    int ret_match = (user_ret == std_ret);

    // 2. Check if the modified destination memory matches perfectly up to the safety buffer limit
    int mem_match = (memcmp(user_dest, std_dest, buffer_size) == 0);

    print_result(test_name, test_num, (ret_match && mem_match));

    free(user_dest);
    free(std_dest);
}

void test_strlcat(void)
{
    printf("--- TESTING ft_strlcat ---\n");

    // Standard baseline validations
    eval_strlcat("Concatenate into plenty of open space", 1, "Hello", " World", 20, 20);
    eval_strlcat("Concatenate with empty source string", 2, "Prefix", "", 15, 15);
    eval_strlcat("Concatenate starting from an empty destination", 3, "", "Data", 10, 10);

    // [MEDIUM LEVEL] 5 Difficult Tests
    eval_strlcat("Medium 1: Size limits truncation mid-way through src string", 4, "Hello", " World", 9, 20);
    eval_strlcat("Medium 2: Size matches destination length exactly (No room to append)", 5, "Hello", " World", 5, 20);
    eval_strlcat("Medium 3: Size parameter is completely 0", 6, "Hello", " World", 0, 20);
    eval_strlcat("Medium 4: Size is smaller than original destination length", 7, "LongSentence", " Append", 4, 25);
    eval_strlcat("Medium 5: Size allows exactly 1 character from source to copy", 8, "Test", "ing", 6, 10);

    // [HARD LEVEL] 5 Difficult Tests
    eval_strlcat("Hard 1: Size parameter vastly exceeds allocated buffer space limits", 9, "Safe", "Copy", 10, 10);
    eval_strlcat("Hard 2: Source string contains an embedded null terminator", 10, "Base", "Hidden\0Bytes", 15, 20);

    // Hard 3: Strict mathematical edge check where size == dest_len + 1 (room for NUL only)
    eval_strlcat("Hard 3: Size fits exactly dest string plus NUL space", 11, "Abc", "Def", 4, 10);

    // Hard 4: Guard byte integrity directly following the active target bounds
    char user_guard[10] = "123\0ZZZZZZ";
    char std_guard[10] = "123\0ZZZZZZ";
    // Appending with size 6 means only 2 characters from "ABCD" can copy ('A','B') + NUL
    strlcat(user_guard, "ABCD", 6);
    std_guard[3] = 'A'; std_guard[4] = 'B'; std_guard[5] = '\0'; // Simulated match
    print_result("Hard 4: Strlcat tracking surrounding guard bytes", 12, (memcmp(user_guard, std_guard, 10) == 0));

    // Hard 5: Extended massive capacity buffer limits
    char dynamic_src[501];
    memset(dynamic_src, 'x', 500);
    dynamic_src[500] = '\0';
    eval_strlcat("Hard 5: Heavy capacity 500-char tracking payload", 13, "Start", dynamic_src, 100, 600);
}

int main(void)
{
	test_strlcat();
	printf("--------------------------\n\n");

    printf("\033[34mALL SUITES EXECUTED SUCCESSFULLY.\033[0m\n");
    return (0);
}
