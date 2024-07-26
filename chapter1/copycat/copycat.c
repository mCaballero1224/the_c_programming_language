#include <stdio.h>

#define BACKSPACE 8
#define TAB 9
#define BACKSLASH 92


/* Exercise 1-9: Write a program to copy its input to its output, replacing
	each tab by '\t', each backspace by '\b', and each backslash 
	by '\\'. This makes the tabs and backspaces visible in an 
	unambiguous way. */


/* NOTE:  May not work depending on how your terminal handles input from your 
	keyboard. Might need to enable raw mode or whatever it may be called 
	on your particular software suite. That or I just messed something up.
	Maybe both. */
int
main()
{
	int c; /* init value to hold user input */

	/* read from user input until EOF received */
	while ((c = getchar()) != EOF) 
	{
		/* if input is one of the special characters (tab, backspact, backslash) */
		if (c == BACKSPACE || c == TAB || c == BACKSLASH)
		{
			/* print the escape slash */
			putchar(BACKSLASH);
			
			/* print the appropriate character based on the value of input */
			if (c == BACKSPACE)
				putchar('b');
			if (c == TAB)
				putchar('t');
			if (c == BACKSLASH)
				putchar(BACKSLASH);
		}
		else 
			putchar(c); /* otherwise, just print the character 
					like normal*/
	}
	return 0;
}
