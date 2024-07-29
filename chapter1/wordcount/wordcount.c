#include <stdlib.h>
#include <ncurses.h>

/* Compile with the following command:
	cc -o wordcount wordcount.c -lncurses 
*/

#define CTRL(x) ((x) & 0x1f)
#define TRUE 1
#define FALSE 0
#define BUFSIZE 1024

/* Prints outro message and cleans up the screen before exiting the program */
int end_program();

/* Prints the status of the buffer and word count */
int print_status(char *buf, int wc, int index, int hidden);

/* Checks to see if a character is a tab, newline, or space */
int is_break_char(char c);

/* Prints a character in bolf font */
int bold_print(char *buf);

/* TODO: Prints the buffer, replacing tabs, newlines
	and spaces with visible characters */
int print_hidden(char buf[]);


/* count lines, words, and characters in input */
int
main()
{
	char buf[BUFSIZE+1] = {0}; /* 29 characters ought to hold most 
				common words in english */
	int ch, char_count, in_word, wc, index, deleted, hidden;
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	/* set init values for state and counts */
	in_word = hidden = FALSE;
	index = char_count = wc = deleted = 0;

	print_status(buf, wc, index, hidden);
	/* read input until receiving EOF */
	while ((ch = getch()) != ERR)
	{
		switch(ch)
		{
			case CTRL('d'):
				return end_program();
			case CTRL('h'):
				hidden = !hidden;
				break;
			case KEY_BACKSPACE:
				if (index > 0)
					--index;
				if (!is_break_char(buf[index]) && is_break_char(buf[index-1]))
				{
					in_word = FALSE;
					--wc;
				}
				buf[index] = 0;
				clear();
				break;
			case '\n':
				in_word = FALSE;
				break;
			case '\t':
				in_word = FALSE;
			case ' ':
				in_word = FALSE;
				break;
			default:
				if (!in_word)
					++wc;
					in_word = TRUE;
				break;
		}

		buf[index] = ((ch != KEY_BACKSPACE) && (ch != CTRL('d')) && ch != CTRL('h')) ? ch : 0;
		if ((index < (BUFSIZE-1)) && ((ch != KEY_BACKSPACE) && (ch != CTRL('h'))))
		{
			++index;
			++char_count;
		}

		if (index == 0)
		{
			wc = 0;
			in_word = FALSE;
		}
		
		clear();
		print_status(buf, wc, index, hidden);
		refresh();
	}
	getch();
	endwin();
	return 0;
}


int 
end_program()
{
	printw("\n\nThank you for using wordcount.\nPress any key to exit.");
	getch();
	endwin();
	return 0;
}

int 
print_status(char *buf, int wc, int index, int hidden)
{
	int last_char = buf[index-1];

	
	printw("Enter input with the keyboard.\n");
	printw("Press Ctrl-D to exit the program.\n");
	printw("Press Ctrl-H to show hidden characters.\n");

	printw("\n=== Status ==");
	printw("\nCurrent index: %d", index);
	printw("\nHidden characters: %s", hidden ? "enabled" : "disabled");
	printw("\nWord count: %d", wc);
	printw("\nBuffer size: %d", BUFSIZE);
	printw("\nRemaining space in buffer: %dB", (BUFSIZE-index-1));

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

	printw("\nSubmitted text:\n");
	if (hidden)
		print_hidden(buf);
	else
		printw("%s", buf);

	return 0;
}

int 
is_break_char(char c) {
	if (c == ' ' || c == '\t' || c == '\n')
		return TRUE;
	else
		return FALSE;
}

int 
bold_print(char *buf)
{
	attron(A_BOLD);
	printw("%s", buf);
	attroff(A_BOLD);
	return 0;
}

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
