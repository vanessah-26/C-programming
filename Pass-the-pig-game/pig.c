#include "names.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum { SIDE = 0, RAZORBACK = 10, TROTTER = 10, SNOUTER = 15, JOWLER = 5 } Position;

const Position pig[7] = {
    SIDE,
    SIDE,
    RAZORBACK,
    TROTTER,
    SNOUTER,
    JOWLER,
    JOWLER,
};
int main(void) {
    int num_players;
    unsigned seed = 2023;

    printf("Number of players (2 to 10)? ");
    int scanf_result_players = scanf("%d", &num_players);

    if (scanf_result_players < 1 || num_players < 2 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        num_players = 2;
    }
    // Prompt the user to input the random seed and validate//

    printf("Random-number seed? ");
    int scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
        seed = 2023;
    }

    // Initialize random number generator seed//
    srandom(seed);

    // Create arrays to store player names and scores//
    const char *player_names[MAX_PLAYERS];
    int player_scores[MAX_PLAYERS] = { 0 };

    // Initialize player names//
    for (int i = 0; i < num_players; i++) {
        player_names[i] = player_name[i];
    }
    // Initialize "has" value for each player's turn //
    int winner = -1; // Initialize to no winner//

    while (winner == -1) {
        for (int player = 0; player < num_players; player++) {
            // Print the name of the player //
            printf("%s\n", player_names[player]);
            // int has = 0;

            while (1) {
                int roll = random() % 7;
                Position position = pig[roll];

                //has += position;//
                player_scores[player] += position;
                // Print the roll and "has" value//
                printf(" rolls %d, has %d\n", position, player_scores[player]);

                if (position == SIDE) {
                    break;

                } else if (player_scores[player] >= 100) {
                    printf("%s won!\n", player_names[player]);
                    winner = player;
                    break;
                }
            }
            if (winner != -1) {
                break;
            }
        }
    }

    return 0;
}
