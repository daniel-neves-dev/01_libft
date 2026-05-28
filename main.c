#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
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
// MOULINETTE EVALUATION ENGINE
// =============================================================================

void    eval_is_functions(const char *name, int num, int (*user_f)(int), int (*std_f)(int), int c)
{
    int user_res = user_f(c);
    int std_res;

    // Protect the standard function from crashing on extreme integer overflows/underflows
    if (c < -1 || c > 255)
        std_res = 0; // Standard behavior defaults to false for out-of-bounds anyway
    else
        std_res = (std_f(c) != 0);

    // Enforce strict 1 or 0 return bounds for your 42 assignment
    if (user_res != 0 && user_res != 1)
        print_result(name, num, 0);
    else
        print_result(name, num, (user_res == std_res));
}

void    eval_isascii(const char *name, int num, int c)
{
    int user_res = ft_isascii(c);
    int std_res = (c >= 0 && c <= 127);

    if (user_res != 0 && user_res != 1)
        print_result(name, num, 0);
    else
        print_result(name, num, (user_res == std_res));
}

void    eval_strlen(const char *name, int num, const char *s)
{
    print_result(name, num, (ft_strlen(s) == strlen(s)));
}

void    eval_memset(const char *name, int num, int c, size_t n)
{
    char buffer_user[150];
    char buffer_std[150];

    memset(buffer_user, 'A', sizeof(buffer_user));
    memset(buffer_std, 'A', sizeof(buffer_std));

    void *ret_user = ft_memset(buffer_user, c, n);
    void *ret_std = memset(buffer_std, c, n);

    int mem_match = (memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);
    int ret_match = (ret_user == buffer_user && ret_std == buffer_std);

    print_result(name, num, (mem_match && ret_match));
}

void    eval_bzero(const char *name, int num, size_t n)
{
    char buffer_user[100];
    char buffer_std[100];

    memset(buffer_user, 'B', sizeof(buffer_user));
    memset(buffer_std, 'B', sizeof(buffer_std));

    ft_bzero(buffer_user, n);
    bzero(buffer_std, n);

    print_result(name, num, (memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0));
}

void    eval_memcpy(const char *name, int num, void *u_dst, const void *u_src, void *s_dst, const void *s_src, size_t n, size_t check_size)
{
    void *ret_user = ft_memcpy(u_dst, u_src, n);
    void *ret_std = memcpy(s_dst, s_src, n);

    int mem_match = 1;
    if (u_dst && s_dst && check_size > 0)
        mem_match = (memcmp(u_dst, s_dst, check_size) == 0);

    int ret_match = (ret_user == u_dst && ret_std == s_dst);
    print_result(name, num, (mem_match && ret_match));
}

void    eval_memmove(const char *name, int num, void *u_dst, const void *u_src, void *s_dst, const void *s_src, size_t n, size_t check_size)
{
    void *ret_user = ft_memmove(u_dst, u_src, n);
    void *ret_std = memmove(s_dst, s_src, n);

    int mem_match = 1;
    if (u_dst && s_dst && check_size > 0)
        mem_match = (memcmp(u_dst, s_dst, check_size) == 0);

    int ret_match = (ret_user == u_dst && ret_std == s_dst);
    print_result(name, num, (mem_match && ret_match));
}

void    eval_strlcpy(const char *name, int num, const char *src, size_t size, size_t buf_size)
{
    char *u_dst = malloc(buf_size);
    char *s_dst = malloc(buf_size);
    memset(u_dst, 'A', buf_size);
    memset(s_dst, 'A', buf_size);

    size_t u_ret = ft_strlcpy(u_dst, src, size);

    // Behavioral twin of standard strlcpy
    size_t s_ret = strlen(src);
    if (size > 0)
    {
        size_t copy_len = (s_ret >= size) ? size - 1 : s_ret;
        memcpy(s_dst, src, copy_len);
        s_dst[copy_len] = '\0';
    }

    print_result(name, num, (u_ret == s_ret && memcmp(u_dst, s_dst, buf_size) == 0));
    free(u_dst);
    free(s_dst);
}

void    eval_strlcat(const char *name, int num, const char *init_dst, const char *src, size_t size, size_t buf_size)
{
    char *u_dst = malloc(buf_size);
    char *s_dst = malloc(buf_size);
    memset(u_dst, 'X', buf_size);
    memset(s_dst, 'X', buf_size);
    strcpy(u_dst, init_dst);
    strcpy(s_dst, init_dst);

    size_t u_ret = ft_strlcat(u_dst, src, size);

    size_t d_len = strlen(s_dst);
    size_t s_len = strlen(src);
    size_t s_ret;

    if (size <= d_len)
        s_ret = size + s_len;
    else
    {
        s_ret = d_len + s_len;
        size_t copy_len = size - d_len - 1;
        if (s_len < copy_len)
            copy_len = s_len;
        memcpy(s_dst + d_len, src, copy_len);
        s_dst[d_len + copy_len] = '\0';
    }

    print_result(name, num, (u_ret == s_ret && memcmp(u_dst, s_dst, buf_size) == 0));
    free(u_dst);
    free(s_dst);
}

void    eval_toupper(const char *name, int num, int c)
{
    int user_res = ft_toupper(c);
    int std_res;

    // Protect standard toupper from crashing or undefined behavior on out-of-bounds ints
    if (c < -1 || c > 255)
        std_res = c; // Standard behavior returns the input unchanged for out-of-bounds
    else
        std_res = toupper(c);

    print_result(name, num, (user_res == std_res));
}

void    eval_tolower(const char *name, int num, int c)
{
    int user_res = ft_tolower(c);
    int std_res;

    // Protect standard tolower from crashing or undefined behavior on out-of-bounds ints
    if (c < -1 || c > 255)
        std_res = c; // Standard behavior returns the input unchanged for out-of-bounds
    else
        std_res = tolower(c);

    print_result(name, num, (user_res == std_res));
}

void    eval_strchr(const char *name, int num, const char *s, int c)
{
    const char *user_res = ft_strchr(s, c);
    const char *std_res = strchr(s, c);

    print_result(name, num, (user_res == std_res));
}

void    eval_strrchr(const char *name, int num, const char *s, int c)
{
    const char *user_res = ft_strrchr(s, c);
    const char *std_res = strrchr(s, c);

    print_result(name, num, (user_res == std_res));
}

void    eval_strncmp(const char *name, int num, const char *s1, const char *s2, size_t n)
{
    int user_res = ft_strncmp(s1, s2, n);
    int std_res = strncmp(s1, s2, n);

    // Normalize results to -1, 1, or 0 since standard returns can vary across systems
    if (user_res < 0) user_res = -1;
    if (user_res > 0) user_res = 1;
    if (std_res < 0) std_res = -1;
    if (std_res > 0) std_res = 1;

    print_result(name, num, (user_res == std_res));
}

// =============================================================================
// TEST SUITE SUITES
// =============================================================================

void test_isalpha(void)
{
    printf("--- TESTING ft_isalpha ---\n");
    // MEDIUM LEVEL
    eval_is_functions("Space character check", 1, ft_isalpha, isalpha, ' ');
    eval_is_functions("Digit 5 check", 2, ft_isalpha, isalpha, '5');
    eval_is_functions("Special character '#'", 3, ft_isalpha, isalpha, '#');
    eval_is_functions("Null terminator validation", 4, ft_isalpha, isalpha, '\0');
    eval_is_functions("Boundary symbol character `", 5, ft_isalpha, isalpha, '`');
    // HARD LEVEL
    eval_is_functions("EOF (-1) processing logic", 6, ft_isalpha, isalpha, -1);
    eval_is_functions("Extended ASCII value 200", 7, ft_isalpha, isalpha, 200);
    eval_is_functions("Integer wrapping INT_MAX limit", 8, ft_isalpha, isalpha, INT_MAX);
    eval_is_functions("Integer wrapping INT_MIN limit", 9, ft_isalpha, isalpha, INT_MIN);
    eval_is_functions("Negative out of bound char handling", 10, ft_isalpha, isalpha, -42);
}

void test_isdigit(void)
{
    printf("--- TESTING ft_isdigit ---\n");
    // MEDIUM LEVEL
    eval_is_functions("Char '0' lowest match", 1, ft_isdigit, isdigit, '0');
    eval_is_functions("Char '9' highest match", 2, ft_isdigit, isdigit, '9');
    eval_is_functions("Alpha letter 'A' negation", 3, ft_isdigit, isdigit, 'A');
    eval_is_functions("Boundary slash character '/'", 4, ft_isdigit, isdigit, '/');
    eval_is_functions("Boundary character ':'", 5, ft_isdigit, isdigit, ':');
    // HARD LEVEL
    eval_is_functions("Raw integer value 5 instead of char", 6, ft_isdigit, isdigit, 5);
    eval_is_functions("EOF character transmission", 7, ft_isdigit, isdigit, -1);
    eval_is_functions("Extended ASCII space 254", 8, ft_isdigit, isdigit, 254);
    eval_is_functions("Overflow ceiling verification", 9, ft_isdigit, isdigit, INT_MAX);
    eval_is_functions("Underflow basement validation", 10, ft_isdigit, isdigit, INT_MIN);
}

void test_isalnum(void)
{
    printf("--- TESTING ft_isalnum ---\n");
    // MEDIUM LEVEL
    eval_is_functions("Punctuation dot symbol negation", 1, ft_isalnum, isalnum, '.');
    eval_is_functions("Whitespace newline check", 2, ft_isalnum, isalnum, '\n');
    eval_is_functions("Boundary char '@' mapping", 3, ft_isalnum, isalnum, '@');
    eval_is_functions("Boundary bracket symbol '['", 4, ft_isalnum, isalnum, '[');
    eval_is_functions("Tabulation key character '\\t'", 5, ft_isalnum, isalnum, '\t');
    // HARD LEVEL
    eval_is_functions("Extended ASCII margin 128", 6, ft_isalnum, isalnum, 128);
    eval_is_functions("Macro EOF transmission processing", 7, ft_isalnum, isalnum, -1);
    eval_is_functions("Deep negative int conversion", 8, ft_isalnum, isalnum, -99);
    eval_is_functions("Extremum parameter integer MAX", 9, ft_isalnum, isalnum, INT_MAX);
    eval_is_functions("Extremum parameter integer MIN", 10, ft_isalnum, isalnum, INT_MIN);
}

void test_isascii(void)
{
    printf("--- TESTING ft_isascii ---\n");
    // MEDIUM LEVEL
    eval_isascii("Standard alphabet literal 'g'", 1, 'g');
    eval_isascii("Null byte index 0 floor edge", 2, 0);
    eval_isascii("Top legitimate ASCII mark 127", 3, 127);
    eval_isascii("Illegal step up ceiling 128", 4, 128);
    eval_isascii("Standard backspace operation index 8", 5, 8);
    // HARD LEVEL
    eval_isascii("Standard negative assignment -1", 6, -1);
    eval_isascii("Deep negative registration -128", 7, -128);
    eval_isascii("Large layout overflow shift 2048", 8, 2048);
    eval_isascii("Maximum capacity allocation check", 9, INT_MAX);
    eval_isascii("Minimum capacity allocation check", 10, INT_MIN);
}

void test_isprint(void)
{
    printf("--- TESTING ft_isprint ---\n");
    // MEDIUM LEVEL
    eval_is_functions("Minimum space threshold ' '", 1, ft_isprint, isprint, ' ');
    eval_is_functions("Maximum string literal tilde '~'", 2, ft_isprint, isprint, '~');
    eval_is_functions("Non-printable control entry DEL 127", 3, ft_isprint, isprint, 127);
    eval_is_functions("Non-printable unit index 31", 4, ft_isprint, isprint, 31);
    eval_is_functions("Tab character escape sequence", 5, ft_isprint, isprint, '\t');
    // HARD LEVEL
    eval_is_functions("Null terminator string boundary", 6, ft_isprint, isprint, '\0');
    eval_is_functions("End of File standard exception (-1)", 7, ft_isprint, isprint, -1);
    eval_is_functions("Overflow registration sequence check", 8, ft_isprint, isprint, INT_MAX);
    eval_is_functions("Underflow registration sequence check", 9, ft_isprint, isprint, INT_MIN);
    eval_is_functions("High memory index unsigned char 255", 10, ft_isprint, isprint, 255);
}

void test_strlen(void)
{
    printf("--- TESTING ft_strlen ---\n");
    // MEDIUM LEVEL
    eval_strlen("Empty string literal detection", 1, "");
    eval_strlen("Space padding string configuration", 2, "     ");
    eval_strlen("Escape control chain configuration", 3, "\n\t\r\v\f");
    eval_strlen("Single character processing check", 4, "x");
    eval_strlen("Standard numeric string pattern", 5, "1234567890");
    // HARD LEVEL
    eval_strlen("Internal early null terminator split", 6, "Hello\0World");
    eval_strlen("Complex specialized symbolic patterns", 7, "!@#$%^&*()_+=-`~[]\\|';:/.,<>?");

    char block_5k[5001];
    memset(block_5k, 'm', 5000); block_5k[5000] = '\0';
    eval_strlen("Massive 5000 byte stack block allocation", 8, block_5k);

    char block_10k[10001];
    memset(block_10k, 'y', 10000); block_10k[10000] = '\0';
    eval_strlen("Massive 10000 byte memory sequence allocation", 9, block_10k);

    eval_strlen("Double embedded inner null blocks", 10, "\0Hidden completely\0");
}

void test_memset(void)
{
    printf("--- TESTING ft_memset ---\n");
    // MEDIUM LEVEL
    eval_memset("Standard filling 5 bytes with 'B'", 1, 'B', 5);
    eval_memset("Standard filling 1 byte minimal unit", 2, 'X', 1);
    eval_memset("Empty processing window with size 0", 3, 'Z', 0);
    eval_memset("Null byte assignment distribution", 4, '\0', 12);
    eval_memset("Complete full scale buffer assignment", 5, 'M', 100);
    // HARD LEVEL
    eval_memset("Overflowing int representation value 300", 6, 300, 15);
    eval_memset("Negative int argument tracking (-10)", 7, -10, 20);
    eval_memset("Severe int assignment value truncation 0x101", 8, 0x101, 20);
    eval_memset("Extreme value alignment check using -1", 9, -1, 40);
    eval_memset("Non-printable raw control bytes code 1", 10, 1, 30);
}

void test_bzero(void)
{
    printf("--- TESTING ft_bzero ---\n");
    // MEDIUM LEVEL
    eval_bzero("Clear zero sequence 5 elements", 1, 5);
    eval_bzero("Clear zero sequence 1 explicit unit", 2, 1);
    eval_bzero("Edge case instruction size 0", 3, 0);
    eval_bzero("Symmetrical half split structural erase", 4, 50);
    eval_bzero("Total space eradication maximum frame", 5, 100);
    // HARD LEVEL
    eval_bzero("Arbitrary prime layout width 13", 6, 13);
    eval_bzero("Arbitrary unaligned structural target 41", 7, 41);
    eval_bzero("Near border trailing clean 99", 8, 99);

    char guard[6] = {'A', 'A', 'A', 'A', 'A', 'G'};
    ft_bzero(guard, 5);
    print_result("Post boundary layout damage check", 9, (guard[5] == 'G'));

    char guard_two[11] = "0123456789";
    ft_bzero(guard_two, 0);
    print_result("Zero check ensuring zero interaction modification", 10, (guard_two[0] == '0'));
}

void test_memcpy(void)
{
    printf("--- TESTING ft_memcpy ---\n");
    char u_buf[100]; char s_buf[100];
    char src[100] = "The quick brown fox jumps over the lazy dog.";

    // MEDIUM LEVEL
    memset(u_buf, 'A', 100); memset(s_buf, 'A', 100);
    eval_memcpy("Standard partial copy segment 15 bytes", 1, u_buf, src, s_buf, src, 15, 100);

    memset(u_buf, 'B', 100); memset(s_buf, 'B', 100);
    eval_memcpy("Embedded inner termination tracking length", 2, u_buf, "Hello\0World", s_buf, "Hello\0World", 11, 100);

    memset(u_buf, 'C', 100); memset(s_buf, 'C', 100);
    eval_memcpy("Minimal unit interaction length 1", 3, u_buf, "Z", s_buf, "Z", 1, 100);

    memset(u_buf, 'D', 100); memset(s_buf, 'D', 100);
    eval_memcpy("Empty size instruction verification 0", 4, u_buf, src, s_buf, src, 0, 100);

    int u_arr[5] = {0}; int s_arr[5] = {0}; int s_src[5] = {42, 1337, -1, 24, 99};
    eval_memcpy("Integer dataset transaction block structures", 5, u_arr, s_src, s_arr, s_src, sizeof(s_src), sizeof(s_src));

    // HARD LEVEL
    memset(u_buf, 'E', 100);
    eval_memcpy("Self assignment address validation safety", 6, u_buf, u_buf, u_buf, u_buf, 30, 100);

    eval_memcpy("Double NULL initialization sequence with 0", 7, NULL, NULL, NULL, NULL, 0, 0);

    struct s_box { char a; int b; char c; } box_src = {'A', 42, 'Z'}, u_box, s_box;
    ft_memcpy(&u_box, &box_src, sizeof(struct s_box));
    memcpy(&s_box, &box_src, sizeof(struct s_box));
    print_result("Struct compilation memory architecture sync", 8, (memcmp(&u_box, &s_box, sizeof(struct s_box)) == 0));

    unsigned char b_src[4] = {255, 128, 0, 42}, u_b[4] = {0}, s_b[4] = {0};
    ft_memcpy(u_b, b_src, 4); memcpy(s_b, b_src, 4);
    print_result("Sign extension unsigned byte loops processing", 9, (memcmp(u_b, s_b, 4) == 0));

    char raw_ctrl[5] = {10, 20, 30, 40, 50}, u_raw[5], s_raw[5];
    eval_memcpy("Raw transmission non-printable unaligned blocks", 10, u_raw, raw_ctrl, s_raw, raw_ctrl, 5, 5);
}

void test_memmove(void)
{
    printf("--- TESTING ft_memmove ---\n");
    char u_buf[60]; char s_buf[60];
    char src[60] = "The quick brown fox jumps over the lazy dog.";
    char u_lap[60]; char s_lap[60];

    // MEDIUM LEVEL
    memset(u_buf, 'A', 60); memset(s_buf, 'A', 60);
    eval_memmove("Clean isolation assignment no crossover", 1, u_buf, src, s_buf, src, 20, 60);

    memset(u_buf, 'B', 60); memset(s_buf, 'B', 60);
    eval_memmove("Single element transition mapping length 1", 2, u_buf, "W", s_buf, "W", 1, 60);

    memset(u_buf, 'C', 60); memset(s_buf, 'C', 60);
    eval_memmove("Neutral execution constraint sequence 0", 3, u_buf, src, s_buf, src, 0, 60);

    int u_i[4] = {0}; int s_i[4] = {0}; int s_is[4] = {100, 200, 300, 400};
    eval_memmove("Integer database row relocation processing", 4, u_i, s_is, s_i, s_is, sizeof(s_is), sizeof(s_is));

    memset(u_buf, 'D', 60);
    eval_memmove("Identical source and destination address match", 5, u_buf, u_buf, u_buf, u_buf, 20, 60);

    // HARD LEVEL (With proper fresh buffer clears before each run)

    // Test 06: Dest > Src (Dest is ahead of Src)
    memset(u_lap, 0, 60); memset(s_lap, 0, 60);
    strcpy(u_lap, "abcdefghijklmnop"); strcpy(s_lap, "abcdefghijklmnop");
    void *ret_u = ft_memmove(u_lap + 5, u_lap, 10);
    void *ret_s = memmove(s_lap + 5, s_lap, 10);
    print_result("Dest greater than source overlap (Backwards copy)", 6, (memcmp(u_lap, s_lap, 60) == 0 && (ret_u == u_lap + 5) && (ret_s == s_lap + 5)));

    // Test 07: Src > Dest (Src is ahead of Dest)
    memset(u_lap, 0, 60); memset(s_lap, 0, 60);
    strcpy(u_lap, "abcdefghijklmnop"); strcpy(s_lap, "abcdefghijklmnop");
    ret_u = ft_memmove(u_lap, u_lap + 5, 10);
    ret_s = memmove(s_lap, s_lap + 5, 10);
    print_result("Source greater than dest overlap (Forwards copy)", 7, (memcmp(u_lap, s_lap, 60) == 0 && (ret_u == u_lap) && (ret_s == s_lap)));

    // Test 08: Shifted by exactly 1 byte
    memset(u_lap, 0, 60); memset(s_lap, 0, 60);
    strcpy(u_lap, "123456789"); strcpy(s_lap, "123456789");
    ret_u = ft_memmove(u_lap + 1, u_lap, 8);
    ret_s = memmove(s_lap + 1, s_lap, 8);
    print_result("Micro structural displacement offset shift 1 byte", 8, (memcmp(u_lap, s_lap, 60) == 0 && (ret_u == u_lap + 1) && (ret_s == s_lap + 1)));

    // Test 09: Double NULL pointer protection
    eval_memmove("Double zero memory allocation null parameters", 9, NULL, NULL, NULL, NULL, 0, 0);

    // Test 10: Complex tracking
    char u_r[30] = "12345678901234567890"; char s_r[30] = "12345678901234567890";
    ret_u = ft_memmove(u_r + 3, u_r + 6, 11);
    ret_s = memmove(s_r + 3, s_r + 6, 11);
    print_result("Complex cross tracking pointer intersection loops", 10, (memcmp(u_r, s_r, 30) == 0 && (ret_u == u_r + 3) && (ret_s == s_r + 3)));
}

void test_strlcpy(void)
{
    printf("--- TESTING ft_strlcpy ---\n");
    // MEDIUM LEVEL
    eval_strlcpy("Abundant safety allocation threshold", 1, "Hello World", 20, 30);
    eval_strlcpy("Perfect exact capacity allocation fit", 2, "12345", 6, 10);
    eval_strlcpy("Empty source sequence transmission logic", 3, "", 5, 10);
    eval_strlcpy("Forced absolute minimum termination layout 1", 4, "Test", 1, 10);
    eval_strlcpy("Symmetrical size boundary matching src string length", 5, "Hello", 5, 10);
    // HARD LEVEL
    eval_strlcpy("Heavy data compression string truncation", 6, "The quick brown fox jumps", 10, 40);
    eval_strlcpy("Absolute execution bypass size rule 0", 7, "Do not copy", 0, 20);
    eval_strlcpy("Massive data allocation tracking payload", 8, "Very long sequence entry compression block data", 4, 10);
    eval_strlcpy("Internal embedded null character tracking split", 9, "Bake\0Cake", 10, 20);

    char u_g[6] = "AAAAA"; char s_g[6] = "AAAAA";
    ft_strlcpy(u_g, "B", 3); s_g[0] = 'B'; s_g[1] = '\0';
    print_result("Post vector memory integrity block tracking", 10, (memcmp(u_g, s_g, 6) == 0));
}

void test_strlcat(void)
{
    printf("--- TESTING ft_strlcat ---\n");
    // MEDIUM LEVEL
    eval_strlcat("Standard connection open room scenario", 1, "Hello", " World", 20, 35);
    eval_strlcat("Null input payload addition execution", 2, "Prefix", "", 15, 25);
    eval_strlcat("Vacant starting sequence address base", 3, "", "Data", 10, 20);
    eval_strlcat("Midway sequence termination truncation split", 4, "Hello", " World", 9, 30);
    eval_strlcat("Strict matching capacity destination line length", 5, "Hello", " World", 5, 30);
    // HARD LEVEL
    eval_strlcat("Absolute execution bypass parameter size 0", 6, "Hello", " World", 0, 30);
    eval_strlcat("Sub floor scale interaction size lower than dest len", 7, "LongSentence", " Append", 4, 40);
    eval_strlcat("Minimal single char truncation space allocation", 8, "Test", "ing", 6, 15);
    eval_strlcat("Internal embedded hidden termination byte chain", 9, "Base", "Hidden\0Bytes", 15, 35);
    eval_strlcat("Precise boundary calculation room for null byte", 10, "Abc", "Def", 4, 15);
}

void test_toupper(void)
{
    printf("--- TESTING ft_toupper ---\n");
    // MEDIUM LEVEL
    eval_toupper("Lowercase 'a' floor match", 1, 'a');
    eval_toupper("Lowercase 'z' ceiling match", 2, 'z');
    eval_toupper("Already uppercase 'M'", 3, 'M');
    eval_toupper("Numeric character '7'", 4, '7');
    eval_toupper("Space character padding", 5, ' ');

    // HARD LEVEL
    eval_toupper("Null terminator passing", 6, '\0');
    eval_toupper("Standard EOF (-1) match", 7, -1);
    eval_toupper("Extended ASCII byte value 150", 8, 150);
    eval_toupper("Extreme overflow allocation INT_MAX", 9, INT_MAX);
    eval_toupper("Extreme underflow allocation INT_MIN", 10, INT_MIN);
}

void test_tolower(void)
{
    printf("--- TESTING ft_tolower ---\n");
    // MEDIUM LEVEL
    eval_tolower("Uppercase 'A' floor match", 1, 'A');
    eval_tolower("Uppercase 'Z' ceiling match", 2, 'Z');
    eval_tolower("Already lowercase 'm'", 3, 'm');
    eval_tolower("Numeric character '3'", 4, '3');
    eval_tolower("Punctuation symbol character '.'", 5, '.');

    // HARD LEVEL
    eval_tolower("Null terminator passing", 6, '\0');
    eval_tolower("Standard EOF (-1) match", 7, -1);
    eval_tolower("Extended ASCII byte value 222", 8, 222);
    eval_tolower("Extreme overflow allocation INT_MAX", 9, INT_MAX);
    eval_tolower("Extreme underflow allocation INT_MIN", 10, INT_MIN);
}

void test_strchr(void)
{
    printf("--- TESTING ft_strchr ---\n");
    const char *str = "The 42 school foundation!";

    // MEDIUM LEVEL
    eval_strchr("Match first character 'T'", 1, str, 'T');
    eval_strchr("Match middle character 's'", 2, str, 's');
    eval_strchr("Match trailing character '!'", 3, str, '!');
    eval_strchr("Match numeric character '4'", 4, str, '4');
    eval_strchr("No match found character 'z'", 5, str, 'z');

    // HARD LEVEL
    // Sneaky 42 Rule: Searching for '\0' must return the pointer to the end of the string
    eval_strchr("Search for explicit null terminator \\0", 6, str, '\0');
    eval_strchr("Search inside an empty string \"\"", 7, "", 'A');
    eval_strchr("Search for \\0 inside an empty string \"\"", 8, "", '\0');

    // Character values are cast to char, handling massive int overflows/underflows safely
    eval_strchr("Overflow int match value (c = 300, maps to ',')", 9, "Hello, World", 300);
    eval_strchr("Negative int match value (c = -2147483585)", 10, "A padded frame", -2147483585);
}

void test_strrchr(void)
{
    printf("--- TESTING ft_strrchr ---\n");
    const char *str = "The 42 school foundation!";
    const char *dup_str = "bonbon";

    // MEDIUM LEVEL
    eval_strrchr("Match unique character 'T'", 1, str, 'T');
    eval_strrchr("Match unique character 's'", 2, str, 's');
    eval_strrchr("Match last occurrence of 'o' in 'bonbon'", 3, dup_str, 'o');
    eval_strrchr("Match last occurrence of 'b' in 'bonbon'", 4, dup_str, 'b');
    eval_strrchr("No match found character 'z'", 5, str, 'z');

    // HARD LEVEL
    // Sneaky 42 Rule: Searching for '\0' must return the pointer to the end of the string
    eval_strrchr("Search for explicit null terminator \\0", 6, str, '\0');
    eval_strrchr("Search inside an empty string \"\"", 7, "", 'A');
    eval_strrchr("Search for \\0 inside an empty string \"\"", 8, "", '\0');

    // Character values are cast to char, handling massive int overflows/underflows safely
    eval_strrchr("Overflow int match value (c = 300, maps to ',')", 9, "Hello, World, again", 300);
    eval_strrchr("Negative int match value (c = -2147483585)", 10, "A padded frame", -2147483585);
}

void test_strncmp(void)
{
    printf("--- TESTING ft_strncmp ---\n");

    // MEDIUM LEVEL
    eval_strncmp("Identical strings comparison", 1, "Hello", "Hello", 5);
    eval_strncmp("Difference within checked boundary n", 2, "abcdef", "abcdeg", 6);
    eval_strncmp("Difference outside checked boundary n", 3, "abcdef", "abcdeg", 5);
    eval_strncmp("First string shorter than second", 4, "abc", "abcdef", 6);
    eval_strncmp("Second string shorter than first", 5, "abcdef", "abc", 6);

    // HARD LEVEL
    // Sneaky 42 Rule: When n is 0, it must return 0 immediately without dereferencing
    eval_strncmp("Zero length evaluation constraint (n = 0)", 6, "A", "B", 0);
    eval_strncmp("Compare with empty string component", 7, "", "test", 4);
    eval_strncmp("Compare two empty strings together", 8, "", "", 5);

    // Unsigned char behavior check (e.g. \200 should be greater than \0)
    eval_strncmp("Extended ASCII unsigned character evaluation", 9, "test\200", "test\0", 6);
    eval_strncmp("Massive length evaluation overflow limit", 10, "Hello", "World", 999999);
}

// =============================================================================
// MAIN FUNCTION RUNNER
// =============================================================================
int main(void)
{
    test_isalpha();   printf("---------------------------------------\n\n");
    test_isdigit();   printf("---------------------------------------\n\n");
    test_isalnum();   printf("---------------------------------------\n\n");
    test_isascii();   printf("---------------------------------------\n\n");
    test_isprint();   printf("---------------------------------------\n\n");
    test_strlen();    printf("---------------------------------------\n\n");
    test_memset();    printf("---------------------------------------\n\n");
    test_bzero();     printf("---------------------------------------\n\n");
    test_memcpy();    printf("---------------------------------------\n\n");
    test_memmove();   printf("---------------------------------------\n\n");
    test_strlcpy();   printf("---------------------------------------\n\n");
    test_strlcat();   printf("---------------------------------------\n\n");
    test_toupper();   printf("---------------------------------------\n\n");
    test_tolower();   printf("---------------------------------------\n\n");
    test_strchr();    printf("---------------------------------------\n\n");
    test_strrchr();   printf("---------------------------------------\n\n");
    test_strncmp();   printf("---------------------------------------\n\n");

    printf("\033[34mALL TEST CONSTRAINTS COMPLETED.\033[0m\n");
    return (0);
}
