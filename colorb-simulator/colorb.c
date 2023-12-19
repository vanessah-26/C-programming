#include "bmp.h"
#include "io.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

void print_help(void) {
    printf("Usage: colorb -i infile -o outfile\n");
    printf("       colorb -h\n");
}

int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;

    // Reading from the command line
    bool i = false, o = false, h = false;
    int ch = 0;

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
        case 'i':
            i = true;
            input_filename = optarg;
            break;
        case 'o':
            o = true;
            output_filename = optarg;
            break;
        case 'h': h = true; break;
        case '?':
            fprintf(stderr, "colorb:  unknown or poorly formatted option %c\n", optopt);
            exit(1);
        }
    }

    if (i && !o) {
        printf("colorb:  -o option is required\n");
        print_help();
    }
    if (!i && o) {
        printf("colorb:  -i option is required\n");
        print_help();
    }
    if (h) {
        print_help();
    }
    if (i && o) {
        //Opening input file
        FILE *fin = fopen(input_filename, "rb");
        if (!fin) {
            printf("error opening input file '%s'.\n", input_filename);
        }

        //Opening output file
        FILE *fout = fopen(output_filename, "wb");
        if (!fout) {
            //fclose(fin); // Close input file before exiting
            printf("error opening output file '%s'.\n", output_filename);
            //fclose(fin);
        }

        printf("Ready to process the image!\n");
        BMP *pbmp = bmp_create(fin); //create bmp structre
        bmp_reduce_palette(pbmp); //process img
        bmp_write(pbmp, fout); //write to outfile

        fclose(fin); //close in file
        fclose(fout); //close out file
        bmp_free(&pbmp);
    }

    return 0;
}
