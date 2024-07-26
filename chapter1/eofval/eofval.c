#include <stdio.h>

int
main()
{

	printf("Enter a character: ");
	int expr = getchar() != EOF;
	/* 1-6: Verify that the expression `getchar() != EOF` is 0 or 1 */
	printf("\nThe expression getchar() != EOF gives the value: %d\n", expr);
	/* 1-7: Write a program to print the value of EOF */
	printf("The value of end-of-file (EOF) is: %d\n", EOF);
}
