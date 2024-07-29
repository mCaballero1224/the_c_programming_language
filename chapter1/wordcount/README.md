# Wordcount

Wordcount takes user input, and gives the character a word count as they enter in text. Like the `copycat` program, I made use of the ncurses library to pull this off. I originally didn't think I'd have to spend too much time on this project. That is, until I thought: "How should I handle backspaces?" This question led to Wordcount becoming a simple text editor rather than a wordcounter. 

<p align="center">
    <img src="https://placehold.co/600x400" alt="Demo of wordcount" />
</p>

User input is stored in a buffer. Depending on the input, the wordcount and state of the buffer is changed. A status message is constantly present, letting the user know that state while they type. 
