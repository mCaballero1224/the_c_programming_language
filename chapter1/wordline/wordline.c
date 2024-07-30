#include <ncurses.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define CTRL(x) ((x) & 0x1f)
#define BUFFSIZE 1024

int end_program();

int clear_input();

int is_break_char(char *c);

int
main()
{
	/* Felt like doing a little work with pointers. */
	char *ch = (char *) malloc(sizeof(char));	/* character holding user input */
	int *cc = (int *) malloc(sizeof(int));		/* character count */
	int *in_word = (int *) malloc(sizeof(int));	/* tracks whether we're in or out of a word*/


	initscr();		/* start ncurses window */
	raw();			/* enable raw mode */
	keypad(stdscr, TRUE);	/* enable keypad input */
	noecho();		/* disable echo upon using getch() */

	*ch = *cc = 0;

	printw("\n == Welcome to Wordline ==");
	printw("\n Enter text via the keyboard, and each word will be printed on a new line.");
	printw("\n Press Ctrl-D to exit the program.");
	printw("\n Enter text here: \n\n ");

	while ((*ch = getch()) != ERR)
	{
		++*cc; /* update character count */
		if (*ch == CTRL('d'))
		{
			--*cc;
			free(ch);
			return end_program();
		}
		else if (is_break_char(ch) && *cc > 0 && *in_word)
		{
			--*cc;
			*in_word = FALSE;
			printw("\n ");
		}
		else
		{
			printw("%c", *ch);
			*in_word = TRUE;
		}

		refresh();
	}

	return 0;
}

int
end_program()
{
	printw("\n\n Thank you for using wordline. Press any key to exit.");
	getch();
	endwin();
	return 0;
}

int
is_break_char(char *ch)
{
	if (*ch == ' ' || *ch == '\t' || *ch == '\n')
		return TRUE;
	else
		return FALSE;
}
