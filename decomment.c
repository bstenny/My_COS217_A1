/*--------------------------------------------------------------------*/
/* decomment.c                                                        */
/* Author: Blake Stenstrom                                            */
/*--------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>

/* These are all the statetypes I use in my dfa */
enum Statetype {CODE, FSLASH, BSLASH, FSTAR, STAR, FSTAR_BSLASH,
        DSTRING, SSTRING, DSTRING_BSLASH, SSTRING_BSLASH};

/* using global variables here. I apologize for not trying to use pointers or something else */
int currentLine;
/* Will be updated when a comment starts and reset to -1 if the comment ends */
int commentLine;

/* handler function for when code is just in a normal state
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state*/
enum Statetype handleCode(int c) {
    enum Statetype state;
    if (c == '/') {
        state = FSLASH;
    }
    else if (c == '"'){
        state = DSTRING;
        putchar(c);
    }
    else if (c == '\''){
        state = SSTRING;
        putchar(c);
    }
    else if (c == '\\') {
        state = BSLASH;
    }
    else{
       if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        state = CODE;
        putchar(c);
    }
    return state;
}
/* handler function for when code encounters a forward slash '\'
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleFSlash(int c) {
    enum Statetype state;
    if (c == '*'){
        state = FSTAR;
        putchar(' ');
        commentLine = currentLine;
    }
    else if (c == '/'){
        state = FSLASH;
        putchar('/');
    }
    else if (c == '"') {
        state = DSTRING;
        putchar('/');
        putchar(c);
    }
    else if (c == '\'') {
        state = SSTRING;
        putchar('/');
        putchar(c);
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        state = CODE;
        putchar('/');
        putchar(c);
    }
    return state;
}
/* handler function for when code is in a comment
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleFStar(int c) {
    enum Statetype state;
    if (c == '*'){
        state = STAR;
    }
    /*
    else if (c == '\\'){
        state = FSTAR_BSLASH;
    } */
    else if (c == 10) { /* This is the newline ASCII character */
        putchar(c);
        currentLine++;
        state = FSTAR;
    }
    else {
        state = FSTAR;
    }
    return state;
}
/* handler function for when the code encounters a star while in a comment
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleStar(int c) {
    enum Statetype state;
    if (c == '/') {
        state = CODE;
        commentLine = -1;
    }
    else if (c == '*'){
        state = STAR;
    }
    else if (c == 10) { /* This is the newline ASCII character */
        putchar(c);
        currentLine++;
        state = FSTAR;
    }
    else {
        state = FSTAR;
    }
    return state;
}
/* handler function for when the code encounters a double quote while in a quote state
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleDString(int c) {
    enum Statetype state;
    if (c == '"'){
        state = CODE;
        putchar(c);
    }
    else if (c == '\\'){
        state = DSTRING_BSLASH;
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        state = DSTRING;
        putchar(c);
    }
    return state;
}

/*handler function for when the code is in a string literal with single quotes
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleSSTRING(int c){
    enum Statetype state;
    if (c == '\''){
        state = CODE;
        putchar(c);
    }
    else if (c == '\\'){
        state = SSTRING_BSLASH;
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        state = SSTRING;
        putchar(c);
    }
    return state;
}

/*handler function for when the code encounters a backslash in normal code
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleBSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        state = CODE;
        putchar('\\');
        putchar('n');
    }
    else if (c == '/'){
        state = FSLASH;
        putchar('\\');
    }
    else if (c == '"') {
        state = DSTRING;
        putchar('\\');
        putchar(c);
    }
    else if (c == '\'') {
        state = SSTRING;
        putchar('\\');
        putchar(c);
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        state = CODE;
        putchar('\\');
        putchar(c);
    }
    return state;
}

/* handler function for when the code encounters a backslash while in a double quote
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleDSTRING_BSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        putchar('\\');
        putchar('n');
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        putchar('\\');
        putchar(c);
    }
    state = DSTRING;
    return state;
}

/* handler function for when the code encounters a backslash while in a single quote
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleSSTRING_BSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        putchar('\\');
        putchar('n');
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        putchar('\\');
        putchar(c);
    }
    state = SSTRING;
    return state;
}

/* handler function for when the code encounters a backslash while in a comment
 * Takes an integer c which will be compared to char values
 * returns an enum Statetype state */
enum Statetype handleFSTAR_BSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        putchar('\\');
        putchar('n');
        state = FSTAR;
    }
    else if (c == '*') {
        state = STAR;
    }
    else {
        if (c == 10) { /* This is the newline ASCII character */
            currentLine++;
        }
        state = FSTAR;
    }
    return state;
}

/* main function
 * Implements the dfa and all associated programs
 * Does not take any arguments
 * Returns an int in the form of EXIT_SUCCESS or EXIT_FAILURE*/
int main(void) {
    int c;
    enum Statetype state = CODE;
    commentLine = -1;
    currentLine = 1;
    while ((c = getchar()) != EOF) {
        switch (state) {
            case CODE:
                state = handleCode(c);
                break;
            case FSLASH:
                state = handleFSlash(c);
                break;
            case BSLASH:
                state = handleBSLASH(c);
                break;
            case FSTAR:
                state = handleFStar(c);
                break;
            case STAR:
                state = handleStar(c);
                break;
            case FSTAR_BSLASH:
                state = handleFSTAR_BSLASH(c);
                break;
            case DSTRING:
                state = handleDString(c);
                break;
            case SSTRING:
                state = handleSSTRING(c);
                break;
            case DSTRING_BSLASH:
                state = handleDSTRING_BSLASH(c);
                break;
            case SSTRING_BSLASH:
                state = handleSSTRING_BSLASH(c);
                break;
        }
    }
    /* This is to handle the edge case that we end on a backslash */
    if (state == BSLASH || state == SSTRING_BSLASH || state == DSTRING_BSLASH) {
        putchar('\\');
    }
    /* This is to handle the edge case that we end on a slash */
    if (state == FSLASH) {
        putchar('/');
    }
    /* These are unacceptable end states */
    if (state == FSTAR || state == STAR) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", commentLine);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}




