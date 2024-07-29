#include <stdlib.h>
#include <ncurses.h>

/* Compile with the following command:
	cc -o wordcount wordcount.c -lncurses 
*/

#define CTRL(x) ((x) & 0x1f)
#define TRUE 1
#define FALSE 0
#define BUFSIZE 64

/* Prints outro message and cleans up the screen before exiting the program */
int end_program();

/* Prints the status of the buffer and word count */
int print_status(char *buf, int wc, int index, int word_status, int hidden);

/* Checks to see if a character is a tab, newline, or space */
int is_break_char(char c);

/* Prints a character in bolf font */
int bold_print(char *buf);

/* Prints the buffer, replacing tabs, newlines
	and spaces with visible characters */
int print_hidden(char buf[]);


/* Main Function */
int
main()
{
	char buf[BUFSIZE+1] = {0}; /* buffer to hold user input */
	int ch, char_count, in_word, wc, index, deleted, hidden; /* initial variables */

	/* start ncurses screen */
	initscr();
	raw();			/* enable raw mode */
	keypad(stdscr, TRUE);   /* enable keypad input */
	noecho();		/* disable echo upon calling getch() */

	/* set init values for state and counts */
	in_word = hidden = FALSE;
	index = char_count = wc = deleted = 0;

	print_status(buf, wc, index, in_word, hidden); /* print initial program status */

	/* read input until receiving EOF */
	while ((ch = getch()) != ERR)
	{
		/* evaluate character given by input */
		switch(ch)
		{
			case CTRL('d'):			/* end the program upon receiving Ctrl-D */
				return end_program();
			case CTRL('h'):			/* view hidden characters upon receiving CTRL-H */
				hidden = !hidden;
				break;
			case KEY_BACKSPACE:		/* Handle backspace */
				if (index > 0)		/* Prevent decrementing outside of the buffer */
					--index;

				/* if the character deleted is a regular character and the previous
					character is a non-visible character (space, tab, newline)
					then we've deleted a word */
				if (!is_break_char(buf[index]) && is_break_char(buf[index-1]))
				{
					/* set in_word state and decrement the word count */
					in_word = FALSE;
					--wc;
				}
				else	/* otherwise, we've deleted an invisible character and gone back into a word */
					in_word = TRUE;

				buf[index] = 0; /* replaced the deleted character with a null character in the buffer */
				clear();
				break;
			case '\n':			/* tabs, spaces, and newlines set the `in_word` status to FALSE */
				in_word = FALSE;
				break;
			case '\t':
				in_word = FALSE;
			case ' ':
				in_word = FALSE;
				break;
			default:	
				if (!in_word)
				{
					++wc;	/* If we're outside of a word and receive a normal character
							update the word count and set the `in_word` state to TRUE */
					in_word = TRUE;
				}
				break;
		}

		/* Place the read character inside of the buffer so long as it isn't
			a backspace, or one of the CTRL keys used in the program. 
			Otherwise, set it to a null character. */
		buf[index] = ((ch != KEY_BACKSPACE) && (ch != CTRL('d')) && ch != CTRL('h')) ? ch : 0;

		/* Update move to the next space in the buffer and update the character count
			so long as we haven't hit the end of the buffer and the read character
			is not a backspace or CTRL-H (CTRL-D is already handled in the switch statement). */
		if ((index <= BUFSIZE) && ((ch != KEY_BACKSPACE) && (ch != CTRL('h'))))
		{
			++index;
			++char_count;
		}

		/* If we've gone all the way to the beginning of the buffer,
			there are no words/characters, which also means we can't
			be inside of a word. */
		if (index == 0)
		{
			wc = 0;
			char_count = 0;
			in_word = FALSE;
		}
		
		/* Clear the screen, print the status of the program, and refresh the screen. */
		clear();
		print_status(buf, wc, index, in_word, hidden);
		refresh();
	}
}


/* Prints an outro message and exits the program. */
int 
end_program()
{
	printw("\n\nThank you for using wordcount.\nPress any key to exit.");
	getch(); /* Wait for user input to close the window. */
	endwin();
	return 0;
}

/* Prints the status of the program along with the contents of the buffer
	holding user input. */
int 
print_status(char *buf, int wc, int index, int word_status, int hidden)
{
	int last_char = buf[index-1];

	
	/* Instructions on using the program. */
	printw("Enter input with the keyboard.\n");
	printw("Press Ctrl-D to exit the program.\n");
	printw("Press Ctrl-H to show hidden characters.\n");

	/* Program Status */
	bold_print("\n=== Status ==");
	printw("\nCurrent index: %d", index);
	printw("\nState: %s", word_status ? "IN word" : "OUT of word");
	printw("\nHidden characters: %s", hidden ? "enabled" : "disabled");
	printw("\nWord count: %d", wc);
	printw("\nBuffer size: %d", BUFSIZE);
	printw("\nRemaining space in buffer: %dB", (BUFSIZE-index));

	/* Handle invisible characters. */
	switch(last_char)
	{
		case '\n':
			printw("\nLast character in buffer: \\n (%d)", last_char);
			break;
		case '\t':
			printw("\nLast character in buffer: \\t (%d)", last_char);
			break;
		case ' ':
			printw("\nLast character in buffer: \\spc (%d)", last_char);
			break;
		default:
			printw("\nLast character in buffer: %c (%d)", last_char, last_char);
			break;
	}

	/* Handle `hidden` state. */
	bold_print("\n\n=== Submitted text ===\n\n");
	if (hidden)
		print_hidden(buf);
	else
		printw("%s", buf);

	return 0;
}

/* Checks if a character is a breaking/invisible character
	(tabs, newlines, spaces). */
int 
is_break_char(char c) {
	if (c == ' ' || c == '\t' || c == '\n')
		return TRUE;
	else
		return FALSE;
}

/* Prints a string literal in bold font to the window. */
int 
bold_print(char *buf)
{
	attron(A_BOLD);
	printw("%s", buf);
	attroff(A_BOLD);
	return 0;
}

/* Prints a buffer, replacing hidden characters (tabs, newlines, spaces)
	with visible representations ('\t', '\n', '\spc'). */
int
print_hidden(char buf[])
{
	int i = 0;

	while (buf[i] != 0)
	{
		switch (buf[i])
		{
			case ' ':
				bold_print("\\spc");
				break;
			case '\t':
				bold_print("\\t");
				break;
			case '\n':
				bold_print("\n\\n");
				break;
			default:
				printw("%c", buf[i]);
				break;
		}
		++i;
	}
	return 0;
}
