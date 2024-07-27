# Copycat

Reads raw input from the keyboard and outputs it to the window. Tabs ('\t'), newlines ('\n'), and backspaces ('\b'), are output as bold characters rather than being rendered, making them visible in an unambiguous way. From what I could tell from the book and reading around online, "The C Programming Language" makes the assumption that your keyboard input is unbuffered, but this is not the case for my environment (i use arch btw). To solve this problem, I made uses of ncurses and the functions found in `<ncurses.h>`. 
