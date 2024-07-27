#include <stdio.h>

#define IN 1	/* inside a word */
#define OUT 0	/* outside a word */

/* count lines, words, and characters in input */
int
main()
{
	int c, nl, nw, nc, state; /* init values */

	/* set init values for state and counts */
	state = OUT;
	nl = nw = nc = 0;

	/* read input until receiving EOF */
	while ((c = getchar()) != EOF)
	{
		++nc;
		if (c == '\n')
		{
			++nl;
		}
		if (c == ' ' || c == '\n' || c == '\t')
		{
			state = OUT;
		}
		else if (state == OUT)
		{
			state = IN;
			++nw;
		}
	}

	printf("\nNewlines: %d\nWords: %d\nTotal Characters: %d\n",
		nl, nw, nc);
}
