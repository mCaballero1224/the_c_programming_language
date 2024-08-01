#include <ncurses.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_LEN 25 /* max word length */
#define CTRL(x) ((x) & 0x1f)

int start_screen();

int is_break_char(int ch);

int print_histogram(int hist[]);

int print_histogram_vertical(int hist[]);

int end_program(int hist[]);

int
main(int argc, char **argv)
{
	int ch, in_word, length, vertical;
int hist[MAX_LEN] = {0};
	in_word = length = 0;


	/* handle option flag */
	if (argc > 1)
	{
		if (strcmp(argv[1], "--vertical") == 0)
		{
			vertical = TRUE;
		}
	}
	




	start_screen();

	printw("\n === Welcome to Wordhist! ===");
	printw("\n Input text via the keyboard.");
	printw("\n Press CTRL-D to see a histogram of word lengths.\n\n ");

	while ((ch = getch()) != ERR)
	{
		if (ch == CTRL('d'))
		{
			if (length > 0)
				++hist[length-1];
			return end_program(hist);
		}
		if (ch == KEY_BACKSPACE)
		{
			continue;
		}
		if (is_break_char(ch) && in_word)
		{
			in_word = FALSE;
			if (length > 0)
				++hist[length-1];
			length = 0;
			printw("%c", ch);
		}
		else 
		{
			if (length <= MAX_LEN)
			{
			++length;
			}
			in_word = TRUE;
			printw("%c", ch);
		}
		refresh();
	}

	return 0;
}

int
start_screen()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	return 0;
}

int
is_break_char(int ch)
{
	return (ch == ' ' || ch == '\n' || ch == '\t');
}

int 
print_histogram(int hist[])
{
	clear();
	int i = 0;

	printw("\n == Results ==");

	while (i < MAX_LEN)
	{
		printw("\n%2d: ", i+1);
		for (int j = 0; j < hist[i]; j++)
			printw("*");
		++i;
		refresh();
	}
	printw("\n\n");
	return 0;
}



int
end_program(int hist[])
{
	print_histogram(hist);
	printw("\n Thank you for using Wordhist!");
	printw("\n Press any key to exit.");
	getch();
	endwin();
	return 0;
}


