#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    int use_libm = 0;

    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'm':
            use_libm = 1; //use the program library
            break;
        case 'h':
            // fprintf(stderr, USAGE, argv[0]);
            printf(USAGE, argv[0]);
            break;
        }
    }

    char input_buffer[1024];
    while (true) {
        fprintf(stderr, "> ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            break; //exitby CtrlD
        }

        char *saveptr;
        char *token = strtok_r(input_buffer, " \n", &saveptr);
        bool binary_error_occurred = false;
        bool unary_error_occurred = false;
        bool bad_char_error_occurred = false;
        bool bad_string_error_occurred = false;

        while (token != NULL) {
            if (strlen(token) == 1) {
                char op = token[0];

                if (binary_operators[(int) op]) {
                    if (!apply_binary_operator(binary_operators[(int) op])
                        && !binary_error_occurred) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        binary_error_occurred = true;
                    }
                } else if (use_libm && libm_unary_operators[(int) op]) {
                    if (!apply_unary_operator(libm_unary_operators[(int) op])
                        && !unary_error_occurred) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        unary_error_occurred = true;
                    }
                } else if (my_unary_operators[(int) op]) {
                    if (!apply_unary_operator(my_unary_operators[(int) op])
                        && !unary_error_occurred) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        unary_error_occurred = true;
                    }
                } else {
                    double num;
                    if (parse_double(token, &num)) {
                        // checking if stack push is successful
                        if (!stack_push(num)) {
				bad_char_error_occurred = true;
				break;
                        }
                    } else if (!bad_char_error_occurred) {
                        fprintf(stderr, ERROR_BAD_CHAR, op);
                        bad_char_error_occurred = true;
                    }
                }

                token = strtok_r(NULL, " \n", &saveptr);
            } else {
                double num;
                if (parse_double(token, &num)) {
                    stack_push(num);
                } else if (!bad_string_error_occurred) {
                    fprintf(stderr, ERROR_BAD_STRING, token);
                    bad_string_error_occurred = true;
                }
                token = strtok_r(NULL, " \n", &saveptr);
            }
        }

        if (binary_error_occurred   || unary_error_occurred 
	 || bad_char_error_occurred || bad_string_error_occurred)
            continue;

        stack_print();
        printf("\n");
        stack_clear();
    }

    return 0;
}
