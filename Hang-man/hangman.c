#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH     256
#define LOSING_MISTAKE 6

//helper function used for sorting eliminated letters//
void sorted_(char *str, char c) {
    size_t len = strlen(str);
    size_t i;

    for (i = 0; i < len; i++) {
        if (c < str[i]) { //check if c < curr char of str//
            break;
        }
    }
    //iterate backward thru str starting from the end and going down to pos. i//
    for (size_t j = len; j > i; j--) {
        str[j] = str[j - 1]; //move each char one pos. to the right to accommodate c//
    }
    str[i] = c;
}
//func to update screen and hangman figure//

void printHangman(int incorrect) {
    printf("%s", CLEAR_SCREEN);
    printf("%s", arts[incorrect]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("wrong number of arguments\n");
        printf("usage: %s <secret word or phrase>\n", argv[0]);
        printf("if the secret is multiple words, you must quote it\n");
        return 1;
    }

    if (strlen(argv[1]) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters\n");
        return 1;
    }

    char curr_phrase[MAX_LENGTH + 1];
    char secret[MAX_LENGTH + 1];
    char elim[26] = "";
    char player_guess;
    int incorrect = 0;

    //Initialize the screen
    // printf("%s", CLEAR_SCREEN);
    //   printf("\n");
    //Cp the secret from the command-line argument
    strcpy(secret, argv[1]);

    if (!validate_secret(secret)) {
        printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
               "apostrophes\n");
        return 1;
    }
    //check if the secret contains punctuation, print out punc shown on Phrase//
    size_t len = strlen(secret);
    for (size_t i = 0; i < len; i++) {
        if (string_contains_character(punctuation, secret[i])) {
            curr_phrase[i] = secret[i];
        } else {
            curr_phrase[i] = '_'; //if not, print _//
        }
    }
    curr_phrase[len] = '\0';

    elim[0] += '\0';

    //game loop//
    //printf("\n");
    //printHangman(incorrect);

    while (incorrect < LOSING_MISTAKE) {
        printHangman(incorrect);
        printf("\n");
        printf("\n");
        printf("    Phrase: %s\n", curr_phrase);

        //print Elimination w/o duplicates//
        char noduped_elim[26] = "";
        size_t noduped_len = 0; //keep track of curr len of noduped_elim arr//
        for (size_t i = 0; i < strlen(elim); i++) {
            if (!string_contains_character(noduped_elim,
                    elim[i])) { //check if the curr eliminated char is existed in noduped_elim arr//
                noduped_elim[noduped_len++] = elim
                    [i]; //increment the arr if that elim char isn't already  existed in the noduped arr//
            }
        }
        noduped_elim[noduped_len] = '\0'; //terminate str by adding nul terminator//
        printf("Eliminated: %s\n\n", noduped_elim);
        //printf("\n");

        bool valid_guess = false;

        while (!valid_guess) {
            //always print the "Guess a letter:" prompt//
            printf("Guess a letter: ");
            player_guess = read_letter();

            if (!is_lowercase_letter(player_guess)) {
                //print the invalid character w/o new line//
                //  printf("%c\n", player_guess);
                //           printf("\b \b"); //to ensure special char or number won't be printed again right in front of new prompt//
                continue; //continue the loop to prompt again//
            } else if (string_contains_character(elim, player_guess)
                       || string_contains_character(curr_phrase, player_guess)) {
                //the player guessed an already eliminated character or one that's in the curr phrase//
                // This is an invalid guess, so continue the loop and prompt again.

            } else {
                valid_guess = true;
                //            printf("\n"); // Print a new line after a valid guess
            }
        }
        //check if player guess appears in secret //
        if (string_contains_character(secret, player_guess)) {
            for (size_t i = 0; i < len; i++) {
                if (secret[i] == player_guess) {
                    if (curr_phrase[i] == '_') {
                        curr_phrase[i] = player_guess; //update underscore w correct guess//
                    }
                }
            }
        } else {
            sorted_(elim, player_guess);
            incorrect++;
            if (incorrect == LOSING_MISTAKE) {
                printHangman(incorrect);
                printf("\n\n");
                printf("    Phrase: %s\n", curr_phrase);
                printf("Eliminated: %s\n\n", elim);
                printf("You lose! The secret phrase was: %s\n", secret);
                return 0;
            }
        }
        //check for winner//
        if (strcmp(secret, curr_phrase) == 0) {
            //printf("\n");
            printHangman(incorrect);
            printf("\n");
            printf("\n");
            printf("    Phrase: %s\n", curr_phrase);
            printf("Eliminated: %s\n\n", noduped_elim);
            //printf("\n");
            printf("You win! The secret phrase was: %s\n", secret);
            return 0;
            //player hast lost//
        } //else if (incorrect == LOSING_MISTAKE) {
        //printf("\n");
        //printHangman(incorrect);
        //printf("\n");
        //printf("\n");
        //printf("    Phrase: %s\n", curr_phrase);
        //printf("Eliminated: %s\n\n", noduped_elim);
        // printf("\n");
        //printf("You lose! The secret phrase was: %s\n", secret);
        //return 0;
        //}
    }
    return 0;
}
