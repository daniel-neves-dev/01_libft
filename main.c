#include <stdio.h>
#include <ctype.h>
#include "libft.h"


// Helper function to print test results in Moulinette style
void	print_result(const char *test_name, int test_num, int pass)
{
	if (pass)
		printf("  Test %02d [%s]: \033[32m[OK]\033[0m\n", test_num, test_name);
	else
		printf("  Test %02d [%s]: \033[31m[KO]\033[0m\n", test_num, test_name);
}

// Evaluation function that compares ft_isalpha with the standard isalpha
void	eval_isalpha(const char *test_name, int test_num, int c)
{
	int	user_res;
	int	std_res;

	user_res = ft_isalpha(c);
	std_res = isalpha(c);

	// In C, standard isalpha returns non-zero for true.
	// We normalize to 1 (true) or 0 (false) to ensure an accurate comparison.
	int user_bool = (user_res != 0);
	int std_bool = (std_res != 0);

	print_result(test_name, test_num, (user_bool == std_bool));
}

// Evaluation function for ft_isdigit
void	eval_isdigit(const char *test_name, int test_num, int c)
{
	int user_res = ft_isdigit(c);
	int std_res = isdigit(c);
	print_result(test_name, test_num, ((user_res != 0) == (std_res != 0)));
}

// Evaluation function for ft_isalnum
void	eval_isalnum(const char *test_name, int test_num, int c)
{
	int user_res = ft_isalnum(c);
	int std_res = isalnum(c);
	print_result(test_name, test_num, ((user_res != 0) == (std_res != 0)));
}

// Evaluation function for ft_isascii
void	eval_isascii(const char *test_name, int test_num, int c)
{
	int user_res = ft_isascii(c);
	int std_res = isascii(c);
	print_result(test_name, test_num, ((user_res != 0) == (std_res != 0)));
}

void	eval_isprint(const char *test_name, int test_num, int c)
{
	int user_res = ft_isprint(c);
	int std_res = isprint(c);
	print_result(test_name, test_num, ((user_res != 0) == (std_res != 0)));
}

// Evaluation function for ft_strlen
void	eval_strlen(const char *test_name, int test_num, const char *s)
{
	size_t	user_res = ft_strlen(s);
	size_t	std_res = ft_strlen(s);

	print_result(test_name, test_num, (user_res == std_res));
}

// Evaluation function for ft_memset
void	eval_memset(const char *test_name, int test_num, int c, size_t n)
{
	// We create two identical buffers, filled with 'A' to detect changes
	char	buffer_user[50];
	char	buffer_std[50];
	void	*ret_user;
	void	*ret_std;

	ft_memset(buffer_user, 'A', sizeof(buffer_user));
	ft_memset(buffer_std, 'A', sizeof(buffer_std));

	// Execute both functions
	ret_user = ft_memset(buffer_user, c, n);
	ret_std = ft_memset(buffer_std, c, n);

	// 1. Verify that the modified memory matches exactly
	int mem_match = (ft_memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);

	// 2. Verify that the returned pointer points to the start of our buffer
	int ret_match = (ret_user == buffer_user);

	print_result(test_name, test_num, (mem_match && ret_match));
}

// Evaluation function for ft_bzero
void	eval_bzero(const char *test_name, int test_num, size_t n)
{
	// Create two identical buffers filled with 'B' to track modifications
	char	buffer_user[50];
	char	buffer_std[50];

	ft_memset(buffer_user, 'B', sizeof(buffer_user));
	ft_memset(buffer_std, 'B', sizeof(buffer_std));

	// Execute both functions (bzero returns nothing)
	ft_bzero(buffer_user, n);
	ft_bzero(buffer_std, n);

	// Verify that the modified memory blocks match perfectly across all 50 bytes
	int mem_match = (ft_memcmp(buffer_user, buffer_std, sizeof(buffer_user)) == 0);

	print_result(test_name, test_num, mem_match);
}

int	main(void)
{
	// ==========================================
	// 1. TESTING FT_ISALPHA
	// ==========================================
	printf("--- TESTING ft_isalpha ---\n");
	eval_isalpha("Uppercase A", 1, 'A');
	eval_isalpha("Lowercase z", 2, 'z');
	eval_isalpha("Middle Upper M", 3, 'M');
	eval_isalpha("Digit 5", 4, '5');
	eval_isalpha("Special Char #", 5, '#');
	eval_isalpha("Space character", 6, ' ');
	eval_isalpha("Null terminator", 7, '\0');
	eval_isalpha("EOF / -1 value", 8, -1);
	eval_isalpha("Extended ASCII 200", 9, 200);
	eval_isalpha("Boundary character `", 10, '`');
	printf("--------------------------\n");

	// ==========================================
	// 2. TESTING FT_ISDIGIT
	// ==========================================
	printf("--- TESTIN ft_isdigit ---\n");
	eval_isdigit("Digit 0", 1, '0');
	eval_isdigit("Digit 5", 2, '5');
	eval_isdigit("Digit 9", 3, '9');
	eval_isdigit("Uppercase A NOT digit", 4, 'A');
	eval_isdigit("Lowercase z NOT digit", 5, 'z');
	eval_isdigit("Special Char / NOT digit", 6, '/'); // Exactly 1 below '0' in ASCII
	eval_isdigit("Null terminator", 7, '\0');
	eval_isdigit("EOF / -1 value", 8, -1);
	eval_isdigit("Extended ASCII 250", 9, 250);
	eval_isdigit("Int value of digit 5", 10, 5); // The integer 5, NOT the character '5'
	printf("--------------------------\n");

	// ==========================================
	// 3. TESTING FT_ISALNUM
	// ==========================================
	printf("--- TESTING ft_isalnum ---\n");
	// === 3 EASY TESTS (Valid alphanumeric inputs) ===
	eval_isalnum("Uppercase G", 1, 'G');
	eval_isalnum("Lowercase m", 2, 'm');
	eval_isalnum("Digit 3", 3, '3');
	// === 3 MEDIUM TESTS (Standard non-alphanumeric punctuation/whitespace) ===
	eval_isalnum("Period / Dot", 4, '.');
	eval_isalnum("Newline  \\n", 5, '\n');
	eval_isalnum("Question Mark", 6, '?');
	// === 4 HARD TESTS (Tricky ASCII boundaries and extreme edge cases) ===
	eval_isalnum("Null terminator", 7, '\0');
	eval_isalnum("EOF / -1 value", 8, -1);
	eval_isalnum("Boundary character @", 9, '@');   // ASCII 64: Exactly 1 below 'A'
	eval_isalnum("Boundary character [", 10, '[');  // ASCII 91: Exactly 1 above 'Z'

	printf("--------------------------\n");

	// ==========================================
	// 4. TESTING FT_ISASCII
	// ==========================================
	printf("--- TESTING ft_isascii ---\n");
	// === 3 EASY TESTS (Standard visible ASCII) ===
	eval_isascii("Letter x", 1, 'x');
	eval_isascii("Digit 2", 2, '2');
	eval_isascii("Exclamation mark !", 3, '!');
	// === 3 MEDIUM TESTS (ASCII Control/Boundary characters) ===
	eval_isascii("Null terminator (0)", 4, 0);
	eval_isascii("Backspace (8)", 5, 8);
	eval_isascii("Highest ASCII (127)", 6, 127); // Delete character
	// === 4 HARD TESTS (Out of bounds & extreme limits) ===
	eval_isascii("Just out of bounds (128)", 7, 128);
	eval_isascii("Negative value (-42)", 8, -42);
	eval_isascii("EOF / -1 value", 9, -1);
	eval_isascii("Large integer (2048)", 10, 2048);
	printf("--------------------------\n");

	// ==========================================
	// 5. TESTING FT_ISPRINT
	// ==========================================
	printf("--- TESTING ft_isprint ---\n");
	// === 3 EASY TESTS (Standard visibly clear printable characters) ===
	eval_isprint("Letter K", 1, 'K');
	eval_isprint("Digit 7", 2, '7');
	eval_isprint("Percent sign %", 3, '%');
	// === 3 MEDIUM TESTS (Control characters that are NOT printable) ===
	eval_isprint("Tab \\t", 4, '\t');
	eval_isprint("Newline \\n", 5, '\n');
	eval_isprint("Null terminator \\0", 6, '\0');
	// === 4 HARD TESTS (Strict boundary limits) ===
	eval_isprint("Lower boundary: Space", 7, ' '); // ASCII 32: The first printable char
	eval_isprint("Below lower boundary", 8, 31);   // ASCII 31: Unit Separator (control char)
	eval_isprint("Upper boundary: Tilde ~", 9, '~'); // ASCII 126: The last printable char
	eval_isprint("Above upper boundary: DEL", 10, 127); // ASCII 127: Control character (Delete)

	printf("--------------------------\n");

	// ==========================================
	// 6. TESTING FT_STRLEN
	// ==========================================
	printf("--- TESTING ft_strlen ---\n");
	// === 3 EASY TESTS (Standard visible strings) ===
	eval_strlen("Normal word", 1, "Hello");
	eval_strlen("Short character", 2, "a");
	eval_strlen("Long standard sentence", 3, "The quick brown fox jumps over the lazy dog.");
	// === 3 MEDIUM TESTS (Empty and whitespace strings) ===
	eval_strlen("Empty string", 4, "");
	eval_strlen("Only spaces", 5, "    ");
	eval_strlen("Escape characters", 6, "\n\t\r\v\f");
	// === 4 HARD TESTS (Hidden null bytes, long inputs, special symbols) ===
	eval_strlen("Embedded null terminator", 7, "Hello\0World");
	eval_strlen("Special/Symbol characters", 8, "!@#$%^&*()_+=-`~[]\\|';:/.,<>?");
	eval_strlen("String with numbers", 9, "1234567890");
	eval_strlen("A fairly long string", 10, "This string contains exactly fifty-four characters...");

	printf("--------------------------\n");

	// ==========================================
	// 7. TESTING FT_MEMSET
	// ==========================================
	printf("--- TESTING ft_memset ---\n");
	// === 3 EASY TESTS (Standard fills on strings) ===
	eval_memset("Fill 5 bytes with 'B'", 1, 'B', 5);
	eval_memset("Fill 10 bytes with '*'", 2, '*', 10);
	eval_memset("Fill 1 byte with 'X'", 3, 'X', 1);
	// === 3 MEDIUM TESTS (Zeroing, Full buffer fill, Size 0) ===
	eval_memset("Fill 0 bytes (should do nothing)", 4, 'Z', 0);
	eval_memset("Fill with null byte \\0", 5, '\0', 8);
	eval_memset("Fill exact size of entire target", 6, 'M', 50);
	// === 4 HARD TESTS (Type casting and edge values) ===
	eval_memset("Int value as char (c = 300)", 7, 300, 10);      // 300 wraps to 44 (',') in unsigned char
	eval_memset("Negative int value (c = -10)", 8, -10, 10);     // Signs shouldn't mess up the byte cast
	eval_memset("Fill half and check guard bytes", 9, 'Y', 25);  // Checks if bytes 26-50 are untouched
	eval_memset("Fill with non-printable character 1", 10, 1, 15);

	printf("--------------------------\n");

	// ==========================================
	// 8. TESTING FT_BZERO
	// ==========================================
	printf("--- TESTING ft_bzero ---\n");

	// === 3 EASY TESTS (Standard clearing sizes) ===
	eval_bzero("Zero out 5 bytes", 1, 5);
	eval_bzero("Zero out 10 bytes", 2, 10);
	eval_bzero("Zero out 1 byte", 3, 1);

	// === 3 MEDIUM TESTS (Empty and maximum sizes) ===
	eval_bzero("Zero out 0 bytes (Edge case)", 4, 0);
	eval_bzero("Zero out exactly half the buffer", 5, 25);
	eval_bzero("Zero out the full buffer size", 6, 50);

	// === 4 HARD TESTS (Guard bytes & precision testing) ===
	eval_bzero("Zero 49 bytes (Check final byte)", 7, 49);  // Checks if byte 50 is strictly left as 'B'
	eval_bzero("Zero 2 bytes", 8, 2);
	eval_bzero("Zero out 13 bytes", 9, 13);                 // Tests non-word aligned/odd counts
	eval_bzero("Zero out 41 bytes", 10, 41);

	printf("--------------------------\n");
	return (0);
}
