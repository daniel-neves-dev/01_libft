#include <stdio.h>

#include <libbsd>

// Note: If you are testing on Linux, you may need to implement your own version
// or link against libbsd, as strnstr is not standard in glibc.

int main() {
	const char *haystack = "Apples, Bananas, and Oranges";

	// Case 1: Match within the length limit
	char *match1 = strnstr(haystack, "Bananas", 20);
	if (match1) {
		printf("Found: %s\n", match1); // Output: "Bananas, and Oranges"
	} else {
		printf("Case 1: Not found\n");
	}

	// Case 2: Substring exists, but falls OUTSIDE the length limit (len = 10)
	char *match2 = strnstr(haystack, "Bananas", 10);
	if (match2) {
		printf("Found: %s\n", match2);
	} else {
		printf("Case 2: Not found (Length limit hit before match completed)\n");
	}

	return 0;
}

