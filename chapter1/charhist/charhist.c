#include <ncurses.h>

#define TRUE 1
#define FALSE 0
#define CHARS 97 /* number of supported characters */
#define CTRL(x) ((x) & 0x1f)

int end_program(int hist[]);

int print_histogram(int hist[]);

int print_warning(char *message);

int 
main()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	
	printw("\n Welcome to Charhist!");
	printw("\n Enter text via the keyboard.");
	printw("\n Press Ctrl-D to show the histogram of characters entered.");
	print_warning("Characters cannot be deleted with backspace.");
	printw("\n\n");
	int ch;

	/* Idexes:
		* 0: tab ('\t')
		* 1: newline ('\n')
		* 2: space (' ')
		* 3 - 94: all other ascii characters excluding DEL
	*/
	int hist[CHARS] = {0};

	while ((ch = getch()) != ERR)
	{
		switch(ch)
		{
			case CTRL('d'):
				return end_program(hist);
			case '\t':
				++hist[0];
				break;
			case '\n':
				++hist[1];
				break;
			case ' ':
				++hist[2];
				break;
			default: 
				++hist[ch-33];
				break;
		}
		printw("%c", ch);
		refresh();
	}
}

int 
print_histogram(int hist[])
{
	clear();
	int i = 0;
	printw("\n == Resultss ==");


	while ( i < CHARS)
	{
		switch(i)
		{
			case 0:
				printw("\n%7s: ", "TAB");
				break;
			case 1: 
				printw("\n%7s: ", "NEWLINE");
				break;
			case 2: 
				printw("\n%7s: ", "SPACE");
				break;
			default:
				printw("\n%7c: ", i+33);
		}
		printw("%d", hist[i]);
		++i;
	}
	printw("\n");
	return 0;
}

int 
end_program(int hist[])
{
	clear();
	printw("\n === Results ===");
	print_histogram(hist);
	printw("\n Thank you for using Charhist!");
	printw("\n Press any key to exit.");
	getch();
	endwin();
	return 0;
}

int
print_warning(char *message)
{
	init_pair(0, COLOR_BLACK, COLOR_RED);
	attron(0);
	attron(A_BOLD);
	printw("\n WARNING: %s", message);
	attroff(A_BOLD);
	attroff(0);
	return 0;
}
