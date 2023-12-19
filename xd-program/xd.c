#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16

void print_ascii(char *buffer, int size, int idx) {
    printf("%08x: ", idx); //print index

    for (int i = 0; i < size; i++) {
        //Print hexa values
        printf("%02x", (unsigned char) buffer[i]);

        //Add space between groups
        if ((i + 1) % 2 == 0) {
            printf(" ");
        }
    }
    //Add spaces at the end
    for (int i = size; i < BUFFER_SIZE; i++) {
        printf("  ");
        if ((i + 1) % 2 == 0) {
            printf(" ");
        }
    }

    printf(" "); //deleted 1 space here

    //Print ASCII representation for last col
    for (int i = 0; i < size; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
    }
    //New line at the end of the last col
    printf("\n");
}
int main(int argc, char *argv[]) {
    int file_descriptor;
    //int opt;

    //Check for the correct num of arguments
    if (argc == 1) {
        file_descriptor = STDIN_FILENO; // Read from stdin
    } else {
        file_descriptor = open(argv[1], O_RDONLY);
        if (file_descriptor == -1) {
            // perror("Error opening fle"); stderr should be empty
            exit(1);
        }
    }

    //Read buffer
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    int totalBR = 0;
    int index = 0;

    /*
    if (file_descriptor == STDIN_FILENO) {
        while ((bytesRead = read(file_descriptor, buffer + totalBR, BUFFER_SIZE)) > 0) {
            //print_ascii(buffer, bytesRead, totalBR);
            // totalBR += bytesRead; //init cmt here
            totalBR += bytesRead;
            if (totalBR == BUFFER_SIZE) {
                print_ascii(buffer, BUFFER_SIZE, index);
                index += totalBR;
                totalBR = 0;
            }
        }


        if (bytesRead == 0
            && totalBR > 0) { //before check if bR == '/0' print extra idx line when ctrlD
            print_ascii(buffer, totalBR, index); //changed here
            return 0;
        }
    } else {
        while ((bytesRead = read(file_descriptor, buffer + totalBR, BUFFER_SIZE)) > 0) {
            totalBR += bytesRead;
            if (totalBR == BUFFER_SIZE) {
                print_ascii(buffer, BUFFER_SIZE, index);
                index += totalBR;
                totalBR = 0;
            }
        }

        

        if (bytesRead == 0 && totalBR > 0) {
            print_ascii(buffer, totalBR, index);
            return 0;
        }
	*/

    while (totalBR < BUFFER_SIZE) {
        bytesRead = read(file_descriptor, buffer + totalBR, (size_t) (BUFFER_SIZE - totalBR));
        //totalBR += bytesRead;
        if (bytesRead <= 0) {
            // print_ascii(buffer, totalBR, index);
            break;
        }
        totalBR += bytesRead;

        if (totalBR >= BUFFER_SIZE) {
            print_ascii(buffer, BUFFER_SIZE, index);
            index += BUFFER_SIZE; //chaged fr totalBR
            totalBR = 0;
        }
    }
    if (totalBR > 0) {
        print_ascii(buffer, totalBR, index);
    }

    close(file_descriptor);

    return 0;
}
