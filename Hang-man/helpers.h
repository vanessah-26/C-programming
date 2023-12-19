#ifndef __HANGMAN_HELP_H__
#define __HANGMAN_HELP_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The longest length that a secret can be.
#define MAX_LENGTH 256

// The player loses as soon as they make their 6th incorrect guess.
#define LOSING_MISTAKE 6

// Printing this string clears the screen.
#define CLEAR_SCREEN "\033[1;1H\033[2J"

bool string_contains_character(const char *s, char c);

char read_letter(void);

bool validate_secret(const char *secret);

bool is_lowercase_letter(char c);

static const char *punctuation = " '-";

static const char *arts[] = { "  _____\n"
                              " |     |\n"
                              "       |\n"
                              "       |\n"
                              "       |\\\n"
                              "       | \\\n"
                              "     __|__\\\n",
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "       |\n"
    "       |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    " |     |\n"
    " |     |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|     |\n"
    " |     |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|\\    |\n"
    " |     |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|\\    |\n"
    " |     |\\\n"
    "/      | \\\n"
    "     __|__\\\n",
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|\\    |\n"
    " |     |\\\n"
    "/ \\    | \\\n"
    "     __|__\\\n" };

#endif
