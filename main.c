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
	return (0);
}
