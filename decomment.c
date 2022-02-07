/*--------------------------------------------------------------------*/
/* decomment.c                                                        */
/* Author: Blake Stenstrom                                            */
/*--------------------------------------------------------------------*/
#include<stdio.h>

enum Statetype {CODE, FSLASH, BSLASH, FSTAR, STAR, FSTAR_BSLASH,
        DSTRING, SSTRING, DSTRING_BSLASH, SSTRING_BSLASH};

/* handler function for when code is just in a normal state */
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
        state = CODE;
        putchar(c);
    }
    return state;
}
/* handler function for when code encounters a forward slash '\' */
enum Statetype handleFSlash(int c) {
    enum Statetype state;
    if (c == '*'){
        state = FSTAR;
        putchar(' ');
    }
    else if (c == '/'){
        state = FSLASH;
        putchar('/');
    }
    else {
        state = CODE;
        putchar('/');
        putchar(c);
    }
    return state;
}
/* handler function for when code is in a comment */
enum Statetype handleFStar(int c) {
    enum Statetype state;
    if (c == '*'){
        state = STAR;
    }
    else if (c == '\\'){
        state = FSTAR_BSLASH;
    }
    else {
        state = FSTAR;
    }
    return state;
}
/* handler function for when the code encounters a star while in a comment */
enum Statetype handleStar(int c) {
    enum Statetype state;
    if (c == '/') {
        state = CODE;
    }
    else if (c == '*'){
        state = STAR;
    }
    else {
        state = FSTAR;
    }
    return state;
}
/* handler function for when the code encounters a double quote while in a quote state*/
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
        state = DSTRING;
        putchar(c);
    }
    return state;
}

/*handler function for when the code enounters a single quote while in a single quote*/
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
        state = SSTRING;
        putchar(c);
    }
    return state;
}

/*handler function for when the code encounters a backslash in normal code*/
enum Statetype handleBSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        state = CODE;
        putchar('\n');
    }
    else {
        state = CODE;
        putchar('\\');
        putchar(c);
    }
    return state;
}

/* handler function for when the code encounters a backslash while in a double quote*/
enum Statetype handleDSTRING_BSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        putchar('\n');
    }
    else {
        putchar('\\');
        putchar(c);
    }
    state = DSTRING;
    return state;
}

/* handler function for when the code encounters a backslash while in a single quote*/
enum Statetype handleSSTRING_BSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        putchar('\n');
    }
    else {
        putchar('\\');
        putchar(c);
    }
    state = SSTRING;
    return state;
}

/* handler function for when the code encounters a backslash while in a comment */
enum Statetype handleFSTAR_BSLASH(int c){
    enum Statetype state;
    if (c == 'n'){
        putchar('\n');
        state = FSTAR;
    }
    else if (c == '*') {
        state = STAR;
    }
    else {
        state = FSTAR;
    }
    return state;
}


int main(void) {
    int c;
    enum Statetype state = CODE;
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
    return 0;
}




