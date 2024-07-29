#include <stdlib.h>
#include <ncurses.h>

/* Compile with the following command:
	cc -o wordcount wordcount.c -lncurses 
*/

#define CTRL(x) ((x) & 0x1f)
#define TRUE 1
#define FALSE 0
#define BUFSIZE 128

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

/* Determines whether a character is one of the control characters used in the
	program */
int is_cntrl(char c);

/* Main Function */
int
main()
{
	char buf[BUFSIZE] = {0}; /* buffer to hold user input */
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
			case CTRL('l'):
				for (int i = 0; i < BUFSIZE; i++)
					buf[i] = 0;
				index = wc = 0;
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
				if (!in_word && (index != BUFSIZE-1)) /* Also check that we're not already at 
										the end of the buffer */
				{
					++wc;	/* If we're outside of a word and receive a normal character
							update the word count and set the `in_word` state to TRUE */
					in_word = TRUE;
				}
				break;
		}

		/* Update move to the next space in the buffer and update the character count
			so long as we haven't hit the end of the buffer and the read character
			is not a backspace or CTRL-H (CTRL-D is already handled in the switch statement). */
		if ((index < BUFSIZE-1) && ((ch != KEY_BACKSPACE) && !is_cntrl(ch)))
		{
			/* Place the read character inside of the buffer so long as it isn't
				a backspace, or one of the CTRL keys used in the program. 
				Otherwise, set it to a null character. */
			buf[index] = ((ch != KEY_BACKSPACE) && !is_cntrl(ch)) ? ch : 0;
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
	printw("\n\n Thank you for using wordcount.\nPress any key to exit.");
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
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	
	/* Instructions on using the program. */
	bold_print("\n === Welcome to Wordcount! ===");
	printw("\n\n Enter input with the keyboard.");
	printw("\n Press Ctrl-D to exit the program.");
	printw("\n Press Ctrl-H to show hidden characters.");
	printw("\n Press Ctrl-L to clear the buffer.");

	/* Program Status */
	bold_print("\n\n === Status ==");
	printw("\n\n Current index: %d", index);
	printw("\n State: %s", word_status ? "IN word" : "OUT of word");
	printw("\n Hidden characters: %s", hidden ? "enabled" : "disabled");
	printw("\n Word count: %d", wc);
	printw("\n Buffer size: %dB", BUFSIZE-1);
	printw("\n Remaining space in buffer: %dB", (BUFSIZE-index-1));


	/* Handle invisible characters. */
	switch(last_char)
	{
		case '\n':
			printw("\n Last character in buffer: \\n (%d)", last_char);
			break;
		case '\t':
			printw("\n Last character in buffer: \\t (%d)", last_char);
			break;
		case ' ':
			printw("\n Last character in buffer: \\spc (%d)", last_char);
			break;
		default:
			printw("\n Last character in buffer: %c (%d)", last_char, last_char);
			break;
	}

	if (index == (BUFSIZE-1))
	{
		attron(COLOR_PAIR(1));
		attron(A_BOLD);
		printw("\n\n Buffer full! Delete characters with backspace, or clear the buffer with Ctrl-L");
		attroff(COLOR_PAIR(1));
		attroff(A_BOLD);
	}

	/* Handle `hidden` state. */
	bold_print("\n\n === Buffer State ===\n\n");
	if (hidden)
		print_hidden(buf);
	else
		printw(" %s", buf);

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

	printw(" ");
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

int
is_cntrl(char c)
{
	if (c == CTRL('h') || c == CTRL('l'))
		return TRUE;
	else return FALSE;
}
