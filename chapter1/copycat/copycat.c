#include <stdlib.h>
#include <ncurses.h> /* used to allow for raw-mode input */


#define CTRL(x) ((x) & 0x1f)
#define FALSE 0
#define TRUE 1

/* NOTE: The version of this program in the book does not make use of ncurses.
	This also means that depending on how your terminal handles input, the
	original version would not be able to handle the input of the
	bakspace character. I learned a little ncurses to get around that. */

/* Prints an outro message before closing the window and
	exiting the program. */
int outro();

/* Prints a string literal in bold to the window */
int bold_print(char *string);

/* Exercise 1-9: Write a program to copy its input to its
	output, replacing each tab by '\t', each backspace 
	by '\b', and each backslash by '\\'. This makes the
	tabs and backspaces visible in an unambiguous way. */
int 
main()
{
	int ch, nc;
	initscr();		/* start curses mode */
	raw();			/* line buffering disabled */
	keypad(stdscr, TRUE);	/* We get F1, F2, etc... */
	noecho();		/* don't echo() while using getch */

	printw("Enter input with the keyboard, and the raw output will be shown on the screen.\n");
	printw("Press Ctrl-D to exit the program.\n\n");

	nc = 0;
	while ((ch = getch()) != ERR)
	{
		if (nc == 80)
		{
			printw("\n");
			nc = 0;
		}
		++nc;
		switch(ch)
		{
			case CTRL('d'):			/* Ctrl-D is usually EOF */
				outro();		/* print outro msg and kill program */
			/* NOTE: Escape characters are printed in bold to
				distinguish them from regular characters. */
			case '\n':			/* Using KEY_ENTER didn't work */
				bold_print("\\n");
				break;
			case '\t':			/* Tab character */
				bold_print("\\t");
				break;
			case KEY_BACKSPACE:		/* Backspace character */
				bold_print("\\b");
				break;
			default:
				printw("%c", ch);
				break;
		}
		refresh(); /* refresh the window */
	}
	outro();
}

int outro()
{
	printw("\nThank you for using copycat!");
	printw("\nPress any key to close the program.");
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
}

int bold_print(char *string)
{
	attron(A_BOLD);		 /* set bold font */
	printw("%s", string);	/* print string literal */
	attroff(A_BOLD);	/* unset bold font */
	return 0;
}
