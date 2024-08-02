#include <stdio.h>      /* printf   */

#define CHARS 94

int print_histogram(int hist[]);

int end_program();

int
main(void)
{
	int ch;
	int hist[CHARS] = {0};

	printf("\nWelcome to Charhist!");
	printf("\nEnter text via the keyboard.");
	printf("\nPress CTRL-D to see the histogram of characters given.\n\n");

	while ((ch = getchar()) != EOF)
	{
		/* Indexes
		* 0 = tab
		* 1 = newline
		* 2 = space
		* 3+ = printable characters
		*/
		switch(ch)
		{
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
		}
	}
	print_histogram(hist);
	end_program();
	return 0;
}

int
print_histogram(int hist[])
{
	printf("\nResults:\n");
	
	int i = 0;
	while (i < CHARS)
	{
		switch(i)
		{
			case 0:
				printf("\n%6s: ", "\\t");
				break;
			case 1:
				printf("\n%6s: ", "\\n");
				break;
			case 2:
				printf("\n%6s: ", "\\spc");
				break;
			default:
				printf("\n%6c: ", i+33);
		}
		for (int j = 0; j < hist[i]; ++j)
		{
			printf("*");
		}
		++i;
	}
	return 0;
}

int
end_program()
{
	printf("\nThank you for using charhist!\n");
	return 0;
}
