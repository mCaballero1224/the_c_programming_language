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

	/* print table header */
	printf("%10s\t%10s\n", "Fahrenheit", "Celsius");
	for (fahr = UPPER; fahr >= LOWER; fahr -= STEP)
	{
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%10.2f\t%10.2f\n", fahr, celsius);
	}
	return 0;
}
