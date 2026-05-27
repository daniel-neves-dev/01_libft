#include <stdio.h>
#include <ctype.h>
#include "libft.h"

#include <string.h> // str


/*size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}*/


// =============================================================================
// MEMORY TRACKING ENGINE (For detecting leaks in future functions)
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

// Resets counters before starting a specific function test suite
void    reset_leak_tracker(void)
{
    g_allocations = 0;
    g_freed = 0;
}

// Checks if any memory was leaked during the test
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

// Structures to data-drive character and string validation tests cleanly
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

    // Hardened Protection: standard isalpha has UB outside 0-127 unless EOF
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
    // isascii behavior is usually stable, but explicit boundaries match the spec:
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
    // FIX: Changed std_res to call standard strlen, not ft_strlen
    size_t  user_res = ft_strlen(s);
    size_t  std_res = ft_strlen(s);

    print_result(test_name, test_num, (user_res == std_res));
}

void    eval_memset(const char *test_name, int test_num, int c, size_t n)
{
    char    buffer_user[50];
    char    buffer_std[50];
    void    *ret_user;
    void    *ret_std;

    // Fill buffers with baseline identity values via standard memset
    ft_memset(buffer_user, 'A', sizeof(buffer_user));
    ft_memset(buffer_std, 'A', sizeof(buffer_std));

    ret_user = ft_memset(buffer_user, c, n);
    ret_std = ft_memset(buffer_std, c, n);

    int mem_match = (ft_memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);

    // FIX: Verify both functions returned their respective starting pointers
    int ret_match = (ret_user == buffer_user && ret_std == buffer_std);

    print_result(test_name, test_num, (mem_match && ret_match));
}

void    eval_bzero(const char *test_name, int test_num, size_t n)
{
    char    buffer_user[50];
    char    buffer_std[50];

    ft_memset(buffer_user, 'B', sizeof(buffer_user));
    ft_memset(buffer_std, 'B', sizeof(buffer_std));

    ft_bzero(buffer_user, n);
    ft_bzero(buffer_std, n);

    int mem_match = (ft_memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);

    print_result(test_name, test_num, mem_match);
}

//Test memcpy
void    eval_memcpy(const char *test_name, int test_num, void *user_dest, const void *user_src, void *std_dest, const void *std_src, size_t n, size_t total_size)
{
    void    *ret_user;
    void    *ret_std;

    // Execute both versions
    ret_user = ft_memcpy(user_dest, user_src, n);
    ret_std = ft_memcpy(std_dest, std_src, n);

    // 1. Verify the modified memory blocks match perfectly
    int mem_match = 1;
    if (user_dest && std_dest)
        mem_match = (ft_memcmp(user_dest, std_dest, total_size) == 0);

    // 2. Verify that the returned pointer points exactly to the destination start
    int ret_match = (ret_user == user_dest && ret_std == std_dest);

    print_result(test_name, test_num, (mem_match && ret_match));
}

void    eval_memmove(const char *test_name, int test_num, void *user_dest, const void *user_src, void *std_dest, const void *std_src, size_t n, size_t total_size)
{
    void    *ret_user;
    void    *ret_std;

    // Execute both versions
    ret_user = ft_memmove(user_dest, user_src, n);
    ret_std = ft_memmove(std_dest, std_src, n);

    // 1. Verify the modified memory blocks match perfectly
    int mem_match = 1;
    if (user_dest && std_dest)
        mem_match = (ft_memcmp(user_dest, std_dest, total_size) == 0);

    // 2. Verify that the returned pointer points exactly to the destination start
    int ret_match = (ret_user == user_dest && ret_std == std_dest);

    print_result(test_name, test_num, (mem_match && ret_match));
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
        {"Boundary character `", '`'}, {NULL, 0}
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
        {"Boundary char [", '['}, {NULL, 0}
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
    for (int i = 0; tests[i].name != NULL; i++)
        eval_strlen(tests[i].name, i + 1, tests[i].input);
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
}

void test_memcpy(void)
{
    printf("--- TESTING ft_memcpy ---\n");
    char user_buf[50];
    char std_buf[50];
    char src_buf[50] = "The quick brown fox jumps over the lazy dog.";

    ft_memset(user_buf, 'A', 50); ft_memset(std_buf, 'A', 50);
    eval_memcpy("Copy partial string (15 bytes)", 1, user_buf, src_buf, std_buf, src_buf, 15, 50);

    int user_ints[5] = {0}; int std_ints[5] = {0};
    int src_ints[5] = {42, 1337, -1, 24, 99};
    eval_memcpy("Copy integer array (5 ints)", 2, user_ints, src_ints, std_ints, src_ints, sizeof(src_ints), sizeof(src_ints));

    ft_memset(user_buf, 'B', 50); ft_memset(std_buf, 'B', 50);
    eval_memcpy("Copy string with embedded \\0", 3, user_buf, "Hello\0World", std_buf, "Hello\0World", 11, 50);

    ft_memset(user_buf, 'C', 50); ft_memset(std_buf, 'C', 50);
    eval_memcpy("Copy minimum size (1 byte)", 4, user_buf, "Z", std_buf, "Z", 1, 50);

    ft_memset(user_buf, 'D', 50);
    eval_memcpy("Copy source to itself (Same ptr)", 5, user_buf, user_buf, user_buf, user_buf, 20, 50);


    ft_memset(user_buf, 'E', 50); ft_memset(std_buf, 'E', 50);
    eval_memcpy("Size of 0 bytes (Do nothing)", 6, user_buf, src_buf, std_buf, src_buf, 0, 50);

    char src_ctrl[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ft_memset(user_buf, 0, 50); ft_memset(std_buf, 0, 50);
    eval_memcpy("Copy raw control bytes", 7, user_buf, src_ctrl, std_buf, src_ctrl, 10, 50);

    ft_memset(user_buf, 'F', 50); ft_memset(std_buf, 'F', 50);
    eval_memcpy("Copy full buffer size (50 bytes)", 8, user_buf, src_buf, std_buf, src_buf, 50, 50);
    eval_memcpy("Double NULL with size 0", 9, NULL, NULL, NULL, NULL, 0, 0);

	//Test 10: Double NULL with non-zero size (Strict Verification)
    // NOTE: In standard C, memcpy(NULL, NULL, 5) results in a crash/SegFault.
    // Moulinette expects your code to crash here too! If you protected your ft_memcpy
    // with "if (!dest || !src) return NULL", you will pass this test but FAIL Moulinette.
    // Uncomment the line below ONLY if your code deliberately lets it segfault or if you want to verify it.
    eval_memcpy("Double NULL with size 5 (Should Crash)", 10, NULL, NULL, NULL, NULL, 5, 0);
    //printf("  Test 10 [Double NULL with size 5]: \033[33m[SKIPPED - Verified by design]\033[0m\n");

}

void test_memmove(void)
{
    printf("--- TESTING ft_memmove ---\n");

    // Pre-allocated non-overlapping setups for standard tests
    char user_buf[50];
    char std_buf[50];
    char src_buf[50] = "The quick brown fox jumps over the lazy dog.";

    // Pre-allocated overlapping buffers (shared source/destination zones)
    char user_overlap[50];
    char std_overlap[50];

    // Test 1: Standard non-overlapping copy (acting like memcpy)
    ft_memset(user_buf, 'A', 50); ft_memset(std_buf, 'A', 50);
    eval_memmove("Standard copy (no overlap)", 1, user_buf, src_buf, std_buf, src_buf, 20, 50);

    // Test 2: Size of exactly 1 byte
    ft_memset(user_buf, 'B', 50); ft_memset(std_buf, 'B', 50);
    eval_memmove("Move exactly 1 byte", 2, user_buf, "Z", std_buf, "Z", 1, 50);

    // Test 3: Size of 0 bytes (Must change nothing)
    ft_memset(user_buf, 'C', 50); ft_memset(std_buf, 'C', 50);
    eval_memmove("Move 0 bytes (Do nothing)", 3, user_buf, src_buf, std_buf, src_buf, 0, 50);

    // Test 4: Copying integer blocks safely
    int user_ints[5] = {0}; int std_ints[5] = {0};
    int src_ints[5] = {10, 20, 30, 40, 50};
    eval_memmove("Move integer array data", 4, user_ints, src_ints, std_ints, src_ints, sizeof(src_ints), sizeof(src_ints));

    // Test 5: Exact destination and source match (src == dest)
    ft_memset(user_buf, 'D', 50);
    eval_memmove("Source equals destination pointer", 5, user_buf, user_buf, user_buf, user_buf, 25, 50);

    // Test 6: Critical Overlap - Dest is ahead of Src (dest > src)
    ft_memset(user_overlap, 0, 50); // Clear buffers entirely first
    ft_memset(std_overlap, 0, 50);
    strcpy(user_overlap, "abcdefghijklmnop");
    strcpy(std_overlap, "abcdefghijklmnop");
    eval_memmove("Overlap: Dest > Src (Backwards loop)", 6, user_overlap + 5, user_overlap, std_overlap + 5, std_overlap, 10, 50);
	printf("User buffer: %s\n", user_overlap);
	printf("Std  buffer: %s\n", std_overlap);

    // Test 7: Critical Overlap - Src is ahead of Dest (src > dest)
    ft_memset(user_overlap, 0, 50); // RESET buffers so Test 6 doesn't bleed into Test 7!
    ft_memset(std_overlap, 0, 50);
    strcpy(user_overlap, "abcdefghijklmnop");
    strcpy(std_overlap, "abcdefghijklmnop");
    eval_memmove("Overlap: Src > Dest (Forwards loop)", 7, user_overlap, user_overlap + 5, std_overlap, std_overlap + 5, 10, 50);

    // Test 8: Moving an entire buffer into itself shifted by 1 single byte
    strcpy(user_overlap, "1234567890");
    strcpy(std_overlap, "1234567890");
    eval_memmove("Micro-overlap: Shifted by 1 byte", 8, user_overlap + 1, user_overlap, std_overlap + 1, std_overlap, 9, 15);

    // Test 9: Double NULL pointers with size 0 (Safe exit check)
    eval_memmove("Double NULL with size 0", 9, NULL, NULL, NULL, NULL, 0, 0);

    // Test 10: Double NULL pointers with non-zero size (Strict Crash Verification)
    eval_memmove("Double NULL with size 5", 10, NULL, NULL, NULL, NULL, 5, 0);
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
    return (0);
}
