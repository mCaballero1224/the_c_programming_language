#include <stdio.h>

#define TAB 9
#define NEWLINE 10
#define BLANK 32

/* Exercise 1-8: Write a program to count blanks,
	tabs, and newlines. */
int
main()
{
	int c, nc, nl, nt, nb; /* init variables */

	nc = nl = nt = nb = 0; /* set counters to 0 */

	/* read user input till EOF received 
	 	store input in c*/
	while ((c = getchar()) != EOF) 
	{
		nc++; /* increment character count */
		if (c == TAB)
			nt++; /* increment tab count */
		if (c == NEWLINE)
			nl++; /* increment newline count */
		if (c == BLANK)
			nb++; /* increment newline count */
	}

	printf("Tab Count: %d\n", nt);
	printf("Newline Count: %d\n", nl);
	printf("Blank Count: %d\n", nb);
	printf("Total Character Count: %d\n", nc);
}
