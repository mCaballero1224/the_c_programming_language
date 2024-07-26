# specialcount

This program reads user input, reads each character and keeps track of the number of characters given. Counts for tabs, newlines, and spaces/blanks are also given. 

<p align="center">
    <img src="https://github.com/mCaballero1224/the_c_programming_language/blob/main/assets/video/specialcounter_demo.gif" />
</p>
<caption>Note to self, cut tail of GIF so that it doesn't show kdenlive</caption>

At the time of writing (Jul 26 2024), the counts include characters deleted by backspace. Another program in chapter one of "The C Programming Langauge" has the reader taking input and replacing backspace with '\b' rather than having it delete a character. 

The program uses preprocessing directives to define the ASCII values for tabs, newlines, and spaces. I could've used comparisons to '\t', '\n', and ' ' respectively, but having the values defined to a number made it easier to think about in my noggin. It also kinda reminds me of setting constants in Assembly.

```
#define TAB 9
#define NEWLINE 10
#define BLANK 32

```

A while loop is used to update a variable containing the latest input from the user before checking it against the ASCII values listed above. Counts are updated until an EOF value is received as input via Ctrl-D. 

```
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
}
```

Upon receiving EOF, the program will display the total characters read from the user, as well as the individual counts for tabs, newlines and blanks.

```
int 
main()
{
    /* initialize variables */
    /* while loop to read characters until EOF received */

    /* print final counts */
	printf("Tab Count: %d\n", nt);
	printf("Newline Count: %d\n", nl);
	printf("Blank Count: %d\n", nb);
	printf("Total Character Count: %d\n", nc);
}
```
