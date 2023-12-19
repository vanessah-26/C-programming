#include "node.h"

#include <stdio.h>
#include <stdlib.h>

//node_create
Node *node_create(uint8_t symbol, uint32_t weight) {
    //alloc a new node
    Node *new_node = (Node *) malloc(sizeof(Node));

    //check if mem allo
    if (new_node == NULL) {
        return NULL;
    }

    //set symbol and weight
    new_node->symbol = symbol;
    new_node->weight = weight;

    //init other fields to default values
    new_node->code = 0;
    new_node->code_length = 0;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

//node_free
void node_free(Node **pnode) {
    if (*pnode != NULL) {
        node_free(&(*pnode)->left);
        node_free(&(*pnode)->right);
        free(*pnode);
        *pnode = NULL;
    }
}

//node_print_tree
void node_print_node(Node *tree, char ch, int indentation);
/*
void node_print_tree(Node *tree) {
    node_print_node(tree, '<', 2);
}*/

void node_print_node(Node *tree, char ch, int indentation) {
    if (tree == NULL)
        return;

    node_print_node(tree->right, '/', indentation + 3);
    printf("%*cweight = %u", indentation + 1, ch, tree->weight);

    if (tree->left == NULL && tree->right == NULL) {
        if (' ' <= tree->symbol && tree->symbol <= '~') {
            printf(", symbol = '%c'", tree->symbol);
        } else {
            printf(", symbol = 0x%02x", tree->symbol);
        }
    }

    printf("\n");
    node_print_node(tree->left, '\\', indentation + 3);
}

void node_print_tree(Node *tree) {
    node_print_node(tree, '<', 2);
}
