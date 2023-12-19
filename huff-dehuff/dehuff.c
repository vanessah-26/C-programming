#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function prototpye
Node **init_stack(void);

// Initialzie a stack and return a pointer to it
Node **init_stack(void) {
    Node **stack = (Node **) calloc(64, sizeof(Node *)); //changed from malloc to calloc
    if (stack == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the stack.\n");
        exit(1);
    }
    return stack;
}

// Push a node onto the stack
void stack_push(Node **stack, Node *node, int *top) {
    if (*top < 63) {
        stack[++(*top)] = node;
    } else {
        fprintf(stderr, "Error: Stack overflow.\n");
        exit(1);
    }
}

// opp a node from the stack
Node *stack_pop(Node **stack, int *top) {
    if (*top >= 0) {
        return stack[(*top)--];
    } else {
        fprintf(stderr, "Error: Stack underflow.\n");
        exit(1);
    }
}

// Free stack
void free_stack(Node **stack) {
    free(stack);
}

// Huffman decoding
void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    // Read header info
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);

    // Check correct file type
    if (type1 != 'H' || type2 != 'C') {
        fprintf(stderr, "Error: Invalid file type.\n");
        exit(1);
    }

    // Calculate number of internal nodes in the tree
    int num_nodes = 2 * num_leaves - 1;

    // Initialize stack
    Node **stack = init_stack();
    int top = -1;

    Node *node;
    // Build Huffman tree
    for (int i = 0; i < num_nodes; i++) {
        // Read one bit from inbuf
        int bit = bit_read_bit(inbuf);

        if (bit == 1) {
            // Leaf node: read symbol
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            // Internal node: pop two nodes from stack
            node = node_create(0, 0);
            node->right = stack_pop(stack, &top);
            node->left = stack_pop(stack, &top);
        }

        // Push the node onto the stack
        stack_push(stack, node, &top);
    }

    // Get the root of Huffman tree
    Node *code_tree = stack_pop(stack, &top);

    // Decode compressed data
    for (uint32_t i = 0; i < filesize; i++) {
        node = code_tree;

        // Traverse the tree until a leaf is reached
        while (1) {
            int bit = bit_read_bit(inbuf);
            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }

            // Check if the node is a leaf
            if (node->left == NULL && node->right == NULL) {
                // Write the symbol to the output file
                fputc(node->symbol, fout);
                break;
            }
        }
    }
    node_free(&code_tree); //added here
    //
    free_stack(stack);
}

#define OPTIONS "i:o:h"

int main(int argc, char *argv[]) {
    bool i = false, o = false, h = false;
    int ch = 0;
    char *infile = NULL;
    FILE *fin = NULL;
    char *outfile = NULL;
    FILE *fout = NULL;
    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
        case 'i':
            i = true;
            // save input file name from optarg
            infile = optarg;
            fin = fopen(infile, "rb");
            if (fin == NULL) {
                fprintf(stderr, "dehuff:  error opening input file %s\n", infile);
                fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
                fprintf(stdout, "       dehuff -h\n");
                exit(1);
            }
            break;
        case 'o':
            o = true;
            outfile = optarg;
            fout = fopen(outfile, "wb");
            if (fout == NULL) {
                fprintf(stderr, "dehuff: error opening output file %s\n", outfile);
                fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
                fprintf(stdout, "       dehuff -h\n");
                fclose(fin); // Close the input file if it was opened
                exit(1);
            }
            break;
        case 'h': h = true; break;
        case '?':
            fprintf(stderr, "dehuff:  unknown or poorly formatted option -%c\n", optopt);
            fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
            fprintf(stdout, "       dehuff -h\n");
            exit(1);
        }
    }
    if (!i && !o && !h) {
        fprintf(stderr, "dehuff:  -i option is required\n");
        fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
        fprintf(stdout, "       dehuff -h\n");
        exit(1);
    }

    if (i && !o) {
        fprintf(stderr, "dehuff:  -o option is required\n");
        fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
        fprintf(stdout, "       dehuff -h\n");
        exit(1);
    }

    if (!i && o) {
        fprintf(stderr, "dehuff:  -i option is required\n");
        fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
        fprintf(stdout, "       dehuff -h\n");
        exit(1);
    }

    if (i && o) {
        // Huffman decoding
        BitReader *inbuf = bit_read_open(infile);
        dehuff_decompress_file(fout, inbuf);

        // Closing files
        fclose(fout);
        fclose(fin);

        //Free BitReader
        bit_read_close(&inbuf);
    }

    if (h) {
        fprintf(stdout, "Usage: dehuff -i infile -o outfile\n");
        fprintf(stdout, "       dehuff -h\n");
    }

    return 0;
}
