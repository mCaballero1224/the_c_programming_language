#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

/* print Fahrenheit-Celsius table
	for fahr = 0, 20, ..., 300 */

int
main()
{
	float fahr, celsius;

	/* NOTE: Exercise 1-3 - modify the program to print 
		a heading above the table */
	printf("%10s\t%10s\n", "Fahrenheit", "Celsius");
	/* Print the table data starting from the upper limit
		and stepping down STEP degrees until
		celcius reaches the lower limit*/
	/* NOTE: Exercise 1-5 - modify the program to print
		the table in reverse order */
	for (fahr = UPPER; fahr >= LOWER; fahr -= STEP)
	{
		/* C = (5/9)(fahr-32) */
		celsius = (5.0/9.0) * (fahr-32.0);
		/* Formatting:
			Two strings, 10 characters long.
			Both strings are left adjusted within 10 characters,
			rounded to two decimal places separated by a horizontal tab 
			with a newline at the end */
		printf("%10.2f\t%10.2f\n", fahr, celsius);
	}
	return 0;
}
