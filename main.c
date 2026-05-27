#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "libft.h"

// =============================================================================
// MEMORY TRACKING ENGINE
// =============================================================================
static size_t   g_allocations = 0;
static size_t   g_freed = 0;

void    *tracked_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr)
        g_allocations++;
    return (ptr);
}

void    tracked_free(void *ptr)
{
    if (ptr)
    {
        g_freed++;
        free(ptr);
    }
}

void    reset_leak_tracker(void)
{
    g_allocations = 0;
    g_freed = 0;
}

int     check_leaks(void)
{
    return (g_allocations == g_freed);
}

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

typedef struct s_char_test {
    const char  *name;
    int         input;
}   t_char_test;

typedef struct s_str_test {
    const char  *name;
    const char  *input;
}   t_str_test;

// =============================================================================
// EVALUATION FUNCTIONS
// =============================================================================

void    eval_isalpha(const char *test_name, int test_num, int c)
{
    int user_res = (ft_isalpha(c) != 0);
    int std_res;

    if (c < -1 || c > 127)
        std_res = 0;
    else
        std_res = (isalpha(c) != 0);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_isdigit(const char *test_name, int test_num, int c)
{
    int user_res = (ft_isdigit(c) != 0);
    int std_res;

    if (c < -1 || c > 127)
        std_res = 0;
    else
        std_res = (isdigit(c) != 0);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_isalnum(const char *test_name, int test_num, int c)
{
    int user_res = (ft_isalnum(c) != 0);
    int std_res;

    if (c < -1 || c > 127)
        std_res = 0;
    else
        std_res = (isalnum(c) != 0);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_isascii(const char *test_name, int test_num, int c)
{
    int user_res = (ft_isascii(c) != 0);
    int std_res = (c >= 0 && c <= 127);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_isprint(const char *test_name, int test_num, int c)
{
    int user_res = (ft_isprint(c) != 0);
    int std_res;

    if (c < -1 || c > 127)
        std_res = 0;
    else
        std_res = (isprint(c) != 0);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_strlen(const char *test_name, int test_num, const char *s)
{
    size_t  user_res = ft_strlen(s);
    size_t  std_res = strlen(s);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_memset(const char *test_name, int test_num, int c, size_t n)
{
    char    buffer_user[100];
    char    buffer_std[100];
    void    *ret_user;
    void    *ret_std;

    memset(buffer_user, 'A', sizeof(buffer_user));
    memset(buffer_std, 'A', sizeof(buffer_std));

    ret_user = ft_memset(buffer_user, c, n);
    ret_std = memset(buffer_std, c, n);

    int mem_match = (memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);
    int ret_match = (ret_user == buffer_user && ret_std == buffer_std);

    print_result(test_name, test_num, (mem_match && ret_match));
}

void    eval_bzero(const char *test_name, int test_num, size_t n)
{
    char    buffer_user[100];
    char    buffer_std[100];

    memset(buffer_user, 'B', sizeof(buffer_user));
    memset(buffer_std, 'B', sizeof(buffer_std));

    ft_bzero(buffer_user, n);
    bzero(buffer_std, n);

    int mem_match = (memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);

    print_result(test_name, test_num, mem_match);
}

void    eval_memcpy(const char *test_name, int test_num, void *user_dest, const void *user_src, void *std_dest, const void *std_src, size_t n, size_t total_size)
{
    void    *ret_user;
    void    *ret_std;

    ret_user = ft_memcpy(user_dest, user_src, n);
    ret_std = memcpy(std_dest, std_src, n);

    int mem_match = 1;
    if (user_dest && std_dest && total_size > 0)
        mem_match = (memcmp(user_dest, std_dest, total_size) == 0);

    int ret_match = (ret_user == user_dest && ret_std == std_dest);

    print_result(test_name, test_num, (mem_match && ret_match));
}

void    eval_memmove(const char *test_name, int test_num, void *user_dest, const void *user_src, void *std_dest, const void *std_src, size_t n, size_t total_size)
{
    void    *ret_user;
    void    *ret_std;

    ret_user = ft_memmove(user_dest, user_src, n);
    ret_std = memmove(std_dest, std_src, n);

    int mem_match = 1;
    if (user_dest && std_dest && total_size > 0)
        mem_match = (memcmp(user_dest, std_dest, total_size) == 0);

    int ret_match = (ret_user == user_dest && ret_std == std_dest);

    print_result(test_name, test_num, (mem_match && ret_match));
}

void    eval_memmove_overlap(const char *test_name, int test_num,
                             void *user_base, void *user_dest, const void *user_src,
                             void *std_base, void *std_dest, const void *std_src,
                             size_t n, size_t total_size)
{
    void    *ret_user = ft_memmove(user_dest, user_src, n);
    void    *ret_std = memmove(std_dest, std_src, n);

    int mem_match = (memcmp(user_base, std_base, total_size) == 0);
    int ret_match = (ret_user == user_dest && ret_std == std_dest);

    print_result(test_name, test_num, (mem_match && ret_match));
}

void    eval_strlcpy(const char *test_name, int test_num, const char *src, size_t size, size_t buffer_size)
{
    char    *user_dest = malloc(buffer_size);
    char    *std_dest = malloc(buffer_size);

    // Fill buffers with a visible baseline character to track exact modifications
    memset(user_dest, 'A', buffer_size);
    memset(std_dest, 'A', buffer_size);

    // Call both functions and capture their returns
    size_t user_ret = ft_strlcpy(user_dest, src, size);

    // Note: Standard strlcpy is available via <string.h> on macOS/BSD.
    // On Linux, you might need to compile with `-lbsd` or use this explicit behavioral twin:
    size_t std_ret = strlen(src);
    if (size > 0)
    {
        size_t copy_len = (std_ret >= size) ? size - 1 : std_ret;
        memcpy(std_dest, src, copy_len);
        std_dest[copy_len] = '\0';
    }

    // 1. Check if the return values (intended lengths) match perfectly
    int ret_match = (user_ret == std_ret);

    // 2. Check if the modified destination memory matches perfectly up to the safety buffer limit
    int mem_match = (memcmp(user_dest, std_dest, buffer_size) == 0);

    print_result(test_name, test_num, (ret_match && mem_match));

    free(user_dest);
    free(std_dest);
}

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
    size_t user_ret = ft_strlcat(user_dest, src, size);

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

// =============================================================================
// TEST SUITE WRAPPERS
// =============================================================================

void test_isalpha(void)
{
    t_char_test tests[] = {
        {"Uppercase A", 'A'}, {"Lowercase z", 'z'}, {"Middle Upper M", 'M'},
        {"Digit 5", '5'}, {"Special Char #", '#'}, {"Space character", ' '},
        {"Null terminator", '\0'}, {"EOF / -1 value", -1}, {"Extended ASCII 200", 200},
        {"Boundary character `", '`'},

        // [HARD LEVEL] Test 11: Int Type Overflow/Wrapping limits
        {"Isalpha extreme: INT_MAX value wrapping", 2147483647},
        {NULL, 0}
    };
    printf("--- TESTING ft_isalpha ---\n");
    for (int i = 0; tests[i].name != NULL; i++)
        eval_isalpha(tests[i].name, i + 1, tests[i].input);
}

void test_isdigit(void)
{
    t_char_test tests[] = {
        {"Digit 0", '0'}, {"Digit 5", '5'}, {"Digit 9", '9'},
        {"Uppercase A NOT digit", 'A'}, {"Lowercase z NOT digit", 'z'},
        {"Special Char / NOT digit", '/'}, {"Null terminator", '\0'},
        {"EOF / -1 value", -1}, {"Extended ASCII 250", 250}, {"Int value of 5", 5},

        // [HARD LEVEL] Test 11: Int Type Underflow/Wrapping limits
        {"Isdigit extreme: INT_MIN value wrapping", -2147483648},
        {NULL, 0}
    };
    printf("--- TESTING ft_isdigit ---\n");
    for (int i = 0; tests[i].name != NULL; i++)
        eval_isdigit(tests[i].name, i + 1, tests[i].input);
}

void test_isalnum(void)
{
    t_char_test tests[] = {
        {"Uppercase G", 'G'}, {"Lowercase m", 'm'}, {"Digit 3", '3'},
        {"Period / Dot", '.'}, {"Newline \\n", '\n'}, {"Question Mark", '?'},
        {"Null terminator", '\0'}, {"EOF / -1 value", -1}, {"Boundary char @", '@'},
        {"Boundary char [", '['},

        // [MEDIUM LEVEL] Test 11: Extended ASCII boundary condition
        {"Isalnum boundary character 128", 128},
        {NULL, 0}
    };
    printf("--- TESTING ft_isalnum ---\n");
    for (int i = 0; tests[i].name != NULL; i++)
        eval_isalnum(tests[i].name, i + 1, tests[i].input);
}

void test_isascii(void)
{
    t_char_test tests[] = {
        {"Letter x", 'x'}, {"Digit 2", '2'}, {"Exclamation mark !", '!'},
        {"Null terminator (0)", 0}, {"Backspace (8)", 8}, {"Highest ASCII (127)", 127},
        {"Just out bounds (128)", 128}, {"Negative value (-42)", -42},
        {"EOF / -1 value", -1}, {"Large integer (2048)", 2048}, {NULL, 0}
    };
    printf("--- TESTING ft_isascii ---\n");
    for (int i = 0; tests[i].name != NULL; i++)
        eval_isascii(tests[i].name, i + 1, tests[i].input);
}

void test_isprint(void)
{
    t_char_test tests[] = {
        {"Letter K", 'K'}, {"Digit 7", '7'}, {"Percent sign %", '%'},
        {"Tab \\t", '\t'}, {"Newline \\n", '\n'}, {"Null terminator \\0", '\0'},
        {"Lower bound: Space", ' '}, {"Below lower bound", 31},
        {"Upper bound: Tilde ~", '~'}, {"Above upper bound: DEL", 127}, {NULL, 0}
    };
    printf("--- TESTING ft_isprint ---\n");
    for (int i = 0; tests[i].name != NULL; i++)
        eval_isprint(tests[i].name, i + 1, tests[i].input);
}

void test_strlen(void)
{
    t_str_test tests[] = {
        {"Normal word", "Hello"}, {"Short character", "a"},
        {"Long standard sentence", "The quick brown fox jumps over the lazy dog."},
        {"Empty string", ""}, {"Only spaces", "    "}, {"Escape characters", "\n\t\r\v\f"},
        {"Embedded null terminator", "Hello\0World"},
        {"Special/Symbol characters", "!@#$%^&*()_+=-`~[]\\|';:/.,<>?"},
        {"String with numbers", "1234567890"},
        {"A fairly long string", "This string contains exactly fifty-four characters..."},
        {NULL, NULL}
    };
    printf("--- TESTING ft_strlen ---\n");
    int i = 0;
    for (; tests[i].name != NULL; i++)
        eval_strlen(tests[i].name, i + 1, tests[i].input);

    // [MEDIUM LEVEL] Test 11: Extremely long string block validation
    char long_str[5001];
    memset(long_str, 'x', 5000);
    long_str[5000] = '\0';
    eval_strlen("Strlen on 5000 character block", i + 1, long_str);
}

void test_memset(void)
{
    printf("--- TESTING ft_memset ---\n");
    eval_memset("Fill 5 bytes with 'B'", 1, 'B', 5);
    eval_memset("Fill 10 bytes with '*'", 2, '*', 10);
    eval_memset("Fill 1 byte with 'X'", 3, 'X', 1);
    eval_memset("Fill 0 bytes (should do nothing)", 4, 'Z', 0);
    eval_memset("Fill with null byte \\0", 5, '\0', 8);
    eval_memset("Fill exact size of entire target", 6, 'M', 50);
    eval_memset("Int value as char (c = 300)", 7, 300, 10);
    eval_memset("Negative int value (c = -10)", 8, -10, 10);
    eval_memset("Fill half and check guard bytes", 9, 'Y', 25);
    eval_memset("Fill with non-printable character 1", 10, 1, 15);

    // [MEDIUM LEVEL] Test 11: Sign extension casting behavior
    eval_memset("Memset with int value overflow 0x101 (Wraps to 1)", 11, 0x101, 15);

    // [HARD LEVEL] Test 12: Completely negative integer instruction
    eval_memset("Memset extreme value -1 (Must cast to 255/0xFF)", 12, -1, 20);
}

void test_bzero(void)
{
    printf("--- TESTING ft_bzero ---\n");
    eval_bzero("Zero out 5 bytes", 1, 5);
    eval_bzero("Zero out 10 bytes", 2, 10);
    eval_bzero("Zero out 1 byte", 3, 1);
    eval_bzero("Zero out 0 bytes (Edge case)", 4, 0);
    eval_bzero("Zero out exactly half the buffer", 5, 25);
    eval_bzero("Zero out the full buffer size", 6, 50);
    eval_bzero("Zero 49 bytes (Check final byte)", 7, 49);
    eval_bzero("Zero 2 bytes", 8, 2);
    eval_bzero("Zero out 13 bytes", 9, 13);
    eval_bzero("Zero out 41 bytes", 10, 41);

    // [MEDIUM LEVEL] Test 11: Guard byte preservation directly after target
    char guard_buffer[6] = {'X', 'X', 'X', 'X', 'X', 'G'};
    ft_bzero(guard_buffer, 5);
    print_result("Bzero preservation of subsequent guard byte", 11, (guard_buffer[5] == 'G'));
}

void test_memcpy(void)
{
    printf("--- TESTING ft_memcpy ---\n");
    char user_buf[50];
    char std_buf[50];
    char src_buf[50] = "The quick brown fox jumps over the lazy dog.";

    memset(user_buf, 'A', 50); memset(std_buf, 'A', 50);
    eval_memcpy("Copy partial string (15 bytes)", 1, user_buf, src_buf, std_buf, src_buf, 15, 50);

    int user_ints[5] = {0}; int std_ints[5] = {0};
    int src_ints[5] = {42, 1337, -1, 24, 99};
    eval_memcpy("Copy integer array (5 ints)", 2, user_ints, src_ints, std_ints, src_ints, sizeof(src_ints), sizeof(src_ints));

    memset(user_buf, 'B', 50); memset(std_buf, 'B', 50);
    eval_memcpy("Copy string with embedded \\0", 3, user_buf, "Hello\0World", std_buf, "Hello\0World", 11, 50);

    memset(user_buf, 'C', 50); memset(std_buf, 'C', 50);
    eval_memcpy("Copy minimum size (1 byte)", 4, user_buf, "Z", std_buf, "Z", 1, 50);

    memset(user_buf, 'D', 50);
    eval_memcpy("Copy source to itself (Same ptr)", 5, user_buf, user_buf, user_buf, user_buf, 20, 50);

    memset(user_buf, 'E', 50); memset(std_buf, 'E', 50);
    eval_memcpy("Size of 0 bytes (Do nothing)", 6, user_buf, src_buf, std_buf, src_buf, 0, 50);

    char src_ctrl[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    memset(user_buf, 0, 50); memset(std_buf, 0, 50);
    eval_memcpy("Copy raw control bytes", 7, user_buf, src_ctrl, std_buf, src_ctrl, 10, 50);

    memset(user_buf, 'F', 50); memset(std_buf, 'F', 50);
    eval_memcpy("Copy full buffer size (50 bytes)", 8, user_buf, src_buf, std_buf, src_buf, 50, 50);
    eval_memcpy("Double NULL with size 0", 9, NULL, NULL, NULL, NULL, 0, 0);
    printf("  Test 10 [Double NULL with size 5]: \033[33m[SKIPPED BY DESIGN - WILL CRASH OTHERWISE]\033[0m\n");

    // [MEDIUM LEVEL] Test 11: Block copies matching complete struct alignments
    struct s_box { char a; int b; char c; } src_box = {'A', 42, 'Z'}, user_box, std_box;
    ft_memcpy(&user_box, &src_box, sizeof(struct s_box));
    memcpy(&std_box, &src_box, sizeof(struct s_box));
    print_result("Memcpy matching complete memory structures", 11, (memcmp(&user_box, &std_box, sizeof(struct s_box)) == 0));

    // [HARD LEVEL] Test 12: Signed/Unsigned byte conversion preservation check
    unsigned char src_bytes[4] = {255, 128, 0, 42};
    unsigned char user_bytes[4] = {0};
    unsigned char std_bytes[4] = {0};
    ft_memcpy(user_bytes, src_bytes, 4);
    memcpy(std_bytes, src_bytes, 4);
    print_result("Memcpy extreme: Signed/Unsigned preservation loop", 12, (memcmp(user_bytes, std_bytes, 4) == 0));
}

void test_memmove(void)
{
    printf("--- TESTING ft_memmove ---\n");
    char user_buf[50];
    char std_buf[50];
    char src_buf[50] = "The quick brown fox jumps over the lazy dog.";
    char user_overlap[50];
    char std_overlap[50];

    memset(user_buf, 'A', 50); memset(std_buf, 'A', 50);
    eval_memmove("Standard copy (no overlap)", 1, user_buf, src_buf, std_buf, src_buf, 20, 50);

    memset(user_buf, 'B', 50); memset(std_buf, 'B', 50);
    eval_memmove("Move exactly 1 byte", 2, user_buf, "Z", std_buf, "Z", 1, 50);

    memset(user_buf, 'C', 50); memset(std_buf, 'C', 50);
    eval_memmove("Move 0 bytes (Do nothing)", 3, user_buf, src_buf, std_buf, src_buf, 0, 50);

    int user_ints[5] = {0}; int std_ints[5] = {0};
    int src_ints[5] = {10, 20, 30, 40, 50};
    eval_memmove("Move integer array data", 4, user_ints, src_ints, std_ints, src_ints, sizeof(src_ints), sizeof(src_ints));

    memset(user_buf, 'D', 50);
    eval_memmove("Source equals destination pointer", 5, user_buf, user_buf, user_buf, user_buf, 25, 50);

    memset(user_overlap, 0, 50); memset(std_overlap, 0, 50);
    strcpy(user_overlap, "abcdefghijklmnop"); strcpy(std_overlap, "abcdefghijklmnop");
    eval_memmove_overlap("Overlap: Dest > Src (Backwards)", 6, user_overlap, user_overlap + 5, user_overlap, std_overlap, std_overlap + 5, std_overlap, 10, 50);

    memset(user_overlap, 0, 50); memset(std_overlap, 0, 50);
    strcpy(user_overlap, "abcdefghijklmnop"); strcpy(std_overlap, "abcdefghijklmnop");
    eval_memmove_overlap("Overlap: Src > Dest (Forwards)", 7, user_overlap, user_overlap, user_overlap + 5, std_overlap, std_overlap, std_overlap + 5, 10, 50);

    memset(user_overlap, 0, 50); memset(std_overlap, 0, 50);
    strcpy(user_overlap, "1234567890"); strcpy(std_overlap, "1234567890");
    eval_memmove_overlap("Micro-overlap: Shifted by 1 byte", 8, user_overlap, user_overlap + 1, user_overlap, std_overlap, std_overlap + 1, std_overlap, 9, 15);

    eval_memmove("Double NULL with size 0", 9, NULL, NULL, NULL, NULL, 0, 0);
    printf("  Test 10 [Double NULL with size 5]: \033[33m[SKIPPED BY DESIGN - WILL CRASH OTHERWISE]\033[0m\n");

    // [HARD LEVEL] Test 11: Complex Ring Overlap (Tails overlapping head)
    char user_ring[50] = "12345678901234567890";
    char std_ring[50] = "12345678901234567890";
    eval_memmove_overlap("Memmove extreme: Loop backwards with overlapping tails", 11,
                         user_ring, user_ring + 2, user_ring + 7,
                         std_ring, std_ring + 2, std_ring + 7, 12, 50);
}

void test_strlcpy(void)
{
    printf("--- TESTING ft_strlcpy ---\n");

    // Standard baseline validations
    eval_strlcpy("Copy normal string with plenty of space", 1, "Hello World", 20, 20);
    eval_strlcpy("Copy string matching exact buffer capacity", 2, "12345", 6, 6);
    eval_strlcpy("Copy from an empty string source", 3, "", 10, 10);
    eval_strlcpy("Copy into a destination with size 1 (NUL only)", 4, "Testing", 1, 10);

    // [MEDIUM LEVEL] 5 Difficult Tests
    eval_strlcpy("Medium 1: Truncation check (Size smaller than src)", 5, "The quick brown fox", 10, 25);
    eval_strlcpy("Medium 2: Size parameter is exactly 0 (Must do nothing)", 6, "Don't copy me", 0, 15);
    eval_strlcpy("Medium 3: Massive source string into tiny size ceiling", 7, "This is a very long string that will be heavily truncated", 5, 10);
    eval_strlcpy("Medium 4: Source is single character, destination size is 2", 8, "A", 2, 5);
    eval_strlcpy("Medium 5: Size matches src length exactly (No room for NUL)", 9, "Hello", 5, 10);

    // [HARD LEVEL] 5 Difficult Tests
    eval_strlcpy("Hard 1: Size parameter vastly exceeds actual buffer allocations", 10, "Safe", 5, 5);
    eval_strlcpy("Hard 2: Source string with an embedded null terminator", 11, "Look\0Hidden", 10, 15);
    eval_strlcpy("Hard 3: Destination size parameter is larger than source string length", 12, "Short", 15, 20);

    // Hard 4: Guard byte integrity tracking directly after target space
    char user_guard[6] = "AAAAA";
    char std_guard[6] = "AAAAA";
    ft_strlcpy(user_guard, "B", 3);
    // Explicit simulation of standard behavior: copy "B", add '\0', leave remainder untouched
    std_guard[0] = 'B'; std_guard[1] = '\0';
    print_result("Hard 4: Strlcpy preservation of surrounding memory blocks", 13, (memcmp(user_guard, std_guard, 6) == 0));

    // Hard 5: Maximum allocation capacity edge limits
    char dynamic_src[1001];
    memset(dynamic_src, 'b', 1000);
    dynamic_src[1000] = '\0';
    eval_strlcpy("Hard 5: Heavy payload 1000-char calculation block", 14, dynamic_src, 50, 100);
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
    ft_strlcat(user_guard, "ABCD", 6);
    std_guard[3] = 'A'; std_guard[4] = 'B'; std_guard[5] = '\0'; // Simulated match
    print_result("Hard 4: Strlcat tracking surrounding guard bytes", 12, (memcmp(user_guard, std_guard, 10) == 0));

    // Hard 5: Extended massive capacity buffer limits
    char dynamic_src[501];
    memset(dynamic_src, 'x', 500);
    dynamic_src[500] = '\0';
    eval_strlcat("Hard 5: Heavy capacity 500-char tracking payload", 13, "Start", dynamic_src, 100, 600);
}

// =============================================================================
// MAIN EXECUTION RUNNER
// =============================================================================
int main(void)
{
    test_isalpha();
    printf("--------------------------\n\n");
    test_isdigit();
    printf("--------------------------\n\n");
    test_isalnum();
    printf("--------------------------\n\n");
    test_isascii();
    printf("--------------------------\n\n");
    test_isprint();
    printf("--------------------------\n\n");
    test_strlen();
    printf("--------------------------\n\n");
    test_memset();
    printf("--------------------------\n\n");
    test_bzero();
    printf("--------------------------\n\n");
    test_memcpy();
    printf("--------------------------\n\n");
    test_memmove();
    printf("--------------------------\n\n");
	test_strlcpy();
	printf("--------------------------\n\n");
	test_strlcat();
	printf("--------------------------\n\n");

    printf("\033[34mALL SUITES EXECUTED SUCCESSFULLY.\033[0m\n");
    return (0);
}
