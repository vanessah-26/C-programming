#include "helpers.h"

bool is_lowercase_letter(char c) {
    //check for lowercase by ASCII value//
    if (c >= 'a'
        && c <= 'z') { //when doing 'a' or 'letter', the computer reads it as ASCII value of that letter//
        return true;
    } else {
        return false;
    }
}

bool validate_secret(const char *secret) {
    int i = 0;
    //traverse through the input phrase//
    while (secret[i] != '\0') {
        char c = secret[i];
        if (!(is_lowercase_letter(c) || c == ' ' || c == '\''
                || c == '-')) { // " \' " to print apostrophe//
            printf("invalid character: '%c'\n", c);
            return false;
        }
        i++; //increment i to next char in the input phrase//
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    int str_len = 0;
    while (s[str_len] != '\0') {
        if (s[str_len] == c) {
            return true;
        }
        str_len++; //to next char in str s//
    }
    return false;
}

//read in player input //
char read_letter(void) {
    int c;

    do {
        c = getchar();
    } while (c == '\n'); //skip newline chas//

    return (char) c;
}
