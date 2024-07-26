# specialcount

This program reads user input, reads each character and keeps track of the number of characters given. Counts for tabs, newlines, and spaces/blanks are also given. 

<p align="center">
    <img src="https://github.com/mCaballero1224/the_c_programming_language/blob/main/assets/video/specialcounter_demo.gif" />
</p>

The program uses preprocessing directives to define the ASCII values for tabs, newlines, and spaces. I could've used comparisons to '\t', '\n', and ' ' respectively, but having the values defined to a number made it easier to think about in my noggin.

```
#define TAB 9
#define NEWLINE 10
#define BLANK 32

```

A while loop is used to update a variable containing the latest input from the user before checking it against the ASCII values listed above. Counts are updated until an EOF value is received as input via Ctrl-D. 
