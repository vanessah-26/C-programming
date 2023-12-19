#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//fill_historgram

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    // Clear all elements of the histogram array
    for (uint32_t i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    // Icrement any two different bins of the histogram
    //0x00 and 0xff match the choice made in the Huffman Code Tree visualizer
    histogram[0x00]++;
    histogram[0xff]++;

    // Initialize the total file size variable
    uint32_t filesize = 0;

    // Read bytes from the file using fgetc()
    int byte;
    while ((byte = fgetc(fin)) != EOF) {
        // Increment the proper element of the histogram
        histogram[byte]++;

        // Increment the total file size
        filesize++;
    }

    // Return the total size of the file
    return filesize;
}

//create_tree
Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    // 1: Create and fill a Priority Queue
    PriorityQueue *priority_queue = pq_create();
    *num_leaves = 0;

    for (uint16_t i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            // Create a node for non-zero histogram entry
            Node *node = node_create((uint8_t) i, histogram[i]);

            // Increment the number of leaves
            (*num_leaves)++;

            // Enqueue the node
            enqueue(priority_queue, node);
        }
    }

    // 2: Run the Huffman Coding algorithm
    while (!pq_is_empty(priority_queue) && !pq_size_is_1(priority_queue)) {
        // Dequeue into left
        Node *left = dequeue(priority_queue);
        // Dequeue into right
        Node *right = dequeue(priority_queue);

        // Create a new node with weight = left->weight + right->weight
        Node *node = node_create(0, left->weight + right->weight);
        node->left = left;
        node->right = right;

        // Enqueue the new node
        enqueue(priority_queue, node);
    }

    // 3: Dequeue the queue's only entry and return it
    Node *huffman_tree = dequeue(priority_queue);
    // Free pq
    pq_free(&priority_queue);

    //seg fault when added this
    //node_free(&huffman_tree);

    return huffman_tree;
}

//fill_code_table

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    // Check if the node is internal
    if (node->left != NULL) {
        // Recursive call for the left child
        // No need to append a 0 for the left child; it's already there
        fill_code_table(code_table, node->left, code, code_length + 1);
    }

    if (node->right != NULL) {
        // Append a 1 to code and recurse for the right child
        code |= ((uint64_t) 1 << code_length);
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        // Leaf node: store the Huffman Code
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

// huff_compress_file
void huff_write_tree(BitWriter *outbuf, Node *node);

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    // Huffman Coding headers
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');

    // Write file size and num_leaves
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);

    // Write Huffman tree
    huff_write_tree(outbuf, code_tree);

    // Rewind infile
    //fseek(fin, 0, SEEK_SET);

    // Compress infile using the Huffman codes
    int b;
    while ((b = fgetc(fin)) != EOF) {
        uint64_t code = code_table[b].code; //fixed here follow pseudo
        uint8_t code_length = code_table[b].code_length;

        // Write each bit of the Huffman code
        for (int i = 0; i < code_length; i++) {
            uint8_t bit = (uint8_t) ((code >> i) & 1);
            bit_write_bit(outbuf, bit);
        }
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        // Leaf node
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        // Internal node
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

//main program provides CLI

#define OPTIONS "i:o:h"

int main(int argc, char *argv[]) {
    bool i = false, o = false, h = false;
    int ch = 0;
    char *infile = NULL;
    FILE *fin = NULL;
    char *outfile = NULL;
    //FILE *fout = NULL;
    uint32_t filesize;

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
        case 'i':
            i = true;
            //save input file name from optarg
            infile = optarg;
            fin = fopen(infile, "rb");
            if (fin == NULL) {
                fprintf(stderr, "huff:  error reading input file %s\n", infile);
                fprintf(stdout, "Usage: huff -i infile -o outfile\n");
                fprintf(stdout, "       huff -h\n");
                exit(1);
            }
            break;
        case 'o':
            o = true;
            outfile = optarg;
            /*fout = fopen(outfile, "wb");
            if (fout == NULL) {
                fprintf(stderr, "huff: error opening  output file %s\n", outfile);
                fclose(fin); // Close the input file if it was opened
                exit(1);
            }*/
            break;
        case 'h': h = true; break;
        case '?':
            fprintf(stderr, "huff:  unknown or poorly formatted option -%c\n", optopt);
            fprintf(stdout, "Usage: huff -i infile -o outfile\n");
            fprintf(stdout, "       huff -h\n");
            exit(1);
        }
    }

    if (!i && !o && !h) {
        fprintf(stderr, "huff:  -i option is required\n");
        fprintf(stdout, "Usage: huff -i infile -o outfile\n");
        fprintf(stdout, "       huff -h\n");
        exit(1);
    }

    if (i && !o) {
        fprintf(stderr, "huff:  -o option is required\n");
        fprintf(stdout, "Usage: huff -i infile -o outfile\n");
        fprintf(stdout, "       huff -h\n");
        exit(1);
    }

    if (!i && o) {
        fprintf(stderr, "huff:  -i option is required\n");
        fprintf(stdout, "Usage: huff -i infile -o outfile\n");
        fprintf(stdout, "       huff -h\n");
        exit(1);
    }

    if (i && o) {
        // Huffman encoding
        // Rewind the input file before passing it to huff_compress_file
        fseek(fin, 0, SEEK_SET);

        uint32_t histogram[256];
        uint16_t num_leaves;
        filesize = fill_histogram(fin, histogram);
        Node *code_tree = create_tree(histogram, &num_leaves);

        Code code_table[256];
        fill_code_table(code_table, code_tree, 0, 0);
        BitWriter *outbuf = bit_write_open(outfile);

        //Added another one here: Rewind the input file before compressing
        fseek(fin, 0, SEEK_SET);

        huff_compress_file(outbuf, fin, filesize, num_leaves, code_tree, code_table);

        node_free(&code_tree);
        //cl the file
        fclose(fin);

        //Free BitWriter
        bit_write_close(&outbuf);
    }

    if (h) {
        fprintf(stdout, "Usage: huff -i infile -o outfile\n");
        fprintf(stdout, "       huff -h\n");
    }

    return 0;
}
