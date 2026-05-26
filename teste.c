#include <stdio.h>
#include <stdlib.h>

int main() {
	char str1[] = "   -4256";
	char str2[] = "123apple";
	char str3[] = "blue321";
	char str4[] = "   --4256";

	int num1 = atoi(str1);
	int num2 = atoi(str2);
	int num3 = atoi(str3);
	int num4 = atoi(str4);

	printf("String: '%s' -> Integer: %d\n", str1, num1);
	printf("String: '%s' -> Integer: %d\n", str2, num2);
	printf("String: '%s' -> Integer: %d\n", str3, num3);
	printf("String: '%s' -> Integer: %d\n", str4, num4);

	return 0;
}


