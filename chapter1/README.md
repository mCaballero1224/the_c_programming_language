# Chapter 1: A Tutorial Introduction

## Exercises
1-1. [x] Run the `hello-world` program on your system. Experiment with leaving out parts of the program, to see what error messages you get.

<ul>
    <li>leaving out the "int" section gives an error that describes "int" as the default return type</li>
</ul>

1-2. [x] Experiment to find out what happens when `printf`'s argument string contains \c, where c is some character not listed above.

<ul>
    <li>"\t" represents a horizontal tab</li>
    <li>"\n" represents a new line</li>
    <li>"\b" represents a backspace</li>
</ul>

1-3. [x] Modify the temperature conversion program `fahr2celsius` to print a heading above the table

1-4. [x] Write a program to print the corresponding Celsius to Fahrenheit table (`celsius2fahr`)

1-5. [x] Modify the temperature conversion programs to print their tables in reverse order.

1-6. [x] Verify that the expression `getchar() != EOF` is `0` or `1`

1-7. [x] Write a program to print the value of EOF.

1-8. [x] Write a program to count blanks, tabs, and newlines.

1-9. [x] Write a program to copy its input to its ouput, replacing each string ofone or more blanks by a single line. 

1-10. [x] Write a program to copy its input to its output, replacing each tab by '\t', each backspace by '\b', and each backslash by '\\'. This makes the tabs and backspaces visible in an unambiguous way. 

1-11. [x] How would you test the `wordcount` program? What kinds of input are most likely to uncover bugs, if there are any?

<ul>
    <li>Backspaces mess up the word count, as they contribute to the character count, and may also mess up the word count depending on the characters removed from input.</li>
    <li>I got around the above point by making use of a buffer to store user input on top of adding some input handling for backspaces.</li>
    <li>The final result feels like a <em>really</em> basic text-editor.</li>
</ul>

1-12. [x] Write a program that prints one word per line.

1-13. [x] Write a program to print a histogram of the lengths of words in its input. 

1-14. [ ] Write a program to print a histogram of the frequences of different characters in its input. 

## Programs
- [`fahr2celsius`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/fahr2celsius): prints a Fahrenheit-Celsius table using a lower limit, upper limit, and step value to increment between the two limits.
- [`celsius2fahr`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/celsius2fahr): prints a Celsius-Fahrenheit table using a similar method as `fahr2celsius`.
- [`copycat`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/copycat): copies keyboard input to stdout, replacing tabs, backspaces, and backslashes with characters.
- [`eofval`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/eofval): small program that evaluates keyboard input comparing it against the value for end-of-file (EOF).
- [`hello-world`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/hello-world): prints a "hello, world" message to the terminal.
- [`specialcount`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/specialcount): copies keyboard input to stdout, counting total characters read, newlines, tabs, and spaces/blanks.
- [`wordcount`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/wordcount): copies keyboard input to stdout, counting words entered.
- [`wordline`](https://github.com/mCaballero1224/the_c_programming_language/tree/main/chapter1/wordline): copies keyboard input to stdout, printing each word on a new line.
