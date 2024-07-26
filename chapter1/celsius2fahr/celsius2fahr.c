#include <stdio.h>

#define LOWER 90	/* lower limit of the table */
#define UPPER 100	/* upper limit of the table */
#define STEP 0.5	/* upper limit of the table */


/* TODO:
 * Add option flags to merge fahr2celsius and celsius2fahr into one program
 * Add option flags to support multiple temperature scales
 * Add option flags to control output
*/

/* NOTE: Exercise 1-5 - write a program to print the corresponding
	Celsius to Fahrenheit table */

int
main()
{
	float fahr, celsius; /* initialize temperature values */

	/* print table header */
	printf("%10s\t%10s\n", "Celsius", "Fahrenheit");

	/* FOR LOOP:
	* Celius value starts at UPPER limit
	* while Celsius is greater than or equal to the LOWER limit
	* convert Celsius value to Fahrenheit
	* print both the Celsius and Fahrenheit values
	* STEP to the next Celsius value to convert
	*/
	for (celsius = UPPER; celsius >= LOWER; celsius -= STEP)
	{
		fahr = ((9.0/5.0) * (celsius)) + 32;
		printf("%10.2f\t%10.2f\n", celsius, fahr);
	}

	return 0;
}
