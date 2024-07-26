# Chapter 1: A Tutorial Introduction

## Exercises
1-1. [x] Run the "hello, wolrd" program on your system. Experiment with leaving out parts of the program, to see what error messages you get.

    - leaving out the "int" section gives an error that describes "int" as the default return type

1-2. [x] Experiment to find out what happens when printf's argument string contains \c, where c is some character not listed above.

    - "\t" represents a horizontal tab
    - "\n" represents a new line
    - "\b" represents a backspace

1-3. [x] Modify the temperature conversion program `fahr2celsius` to print a heading above the table

1-4. [x] Write a program to print the corresponding Celsius to Fahrenheit table (`celsius2fahr`)

1-5. [x] Modify the temperature conversion programs to print their tables in reverse order.

1-6. [ ] Verify that the expression `getchar() != EOF` is `0` or `1`

1-7. [ ] Write a program to print the value of EOF.

1-8. [ ] Write a program to count blanks, tabs, and newlines.

1-9. [ ] Write a program to copy its input to its output, replacing each tab by '\t', each backspace by '\b', and each backslash by '\\'. This makes the tabs and backspaces visible in an unambiguous way. 



## Programs
- [`hello-world`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/hello-world): prints a "hello, world" message to the terminal
- [`fahr2celsius`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/fahr2celsius): prints a Fahrenheit-Celsius table using a lower limit, upper limit, and step value to increment between the two limits
- [`celsius2fahr`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/celsius2fahr): prints a Celsius-Fahrenheit table using a similar method as `fahr2celsius`
