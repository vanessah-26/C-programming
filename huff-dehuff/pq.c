#include "pq.h"

#include "node.h"

#include <assert.h>
#include <stdio.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

//pq_create()

PriorityQueue *pq_create(void) {
    PriorityQueue *newQ = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    //check mem alloc
    if (newQ == NULL) {
        return NULL;
    }

    newQ->list = NULL;

    return newQ;
}

//pq_free()
void pq_free(PriorityQueue **q) {
    //check if there's sth to free
    if (*q != NULL) {
        while ((*q)->list != NULL) {
            ListElement *temp = (*q)->list;
            (*q)->list = temp->next;
            free(temp);
        }

        //free PriorityQueue strctre
        free(*q);

        *q = NULL;
    }
}

//pq_is_empty()
bool pq_is_empty(PriorityQueue *q) {
    return q->list == NULL;
}

//pq_sz_is_1
bool pq_size_is_1(PriorityQueue *q) {
    return q->list != NULL && q->list->next == NULL;
}

//pq_less_than
bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        if (e1->tree->symbol < e2->tree->symbol) {
            return true;
        }
        return false;
    }
    return false;
}

//enqueue func

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new_element = (ListElement *) malloc(sizeof(ListElement));

    if (new_element == NULL) {
        //return NULL;
        exit(1);
    }
    //set the tree field to the value of the tree function parameter
    new_element->tree = tree;

    //if q is empty, point to next new_ele
    if (q->list == NULL) {
        q->list = new_element;
    } else if (pq_less_than(new_element, q->list)) {
        // New element E1 goes before all existing elements of the list
        new_element->next = q->list;
        q->list = new_element;
    } else {
        //look for existing element e2
        ListElement *current = q->list;
        while (current->next != NULL && !pq_less_than(new_element, current->next)) {
            current = current->next;
        }

        //insert after e2
        new_element->next = current->next;
        current->next = new_element;
    }
}

//dequeue

Node *dequeue(PriorityQueue *q) {
    assert(q != NULL);

    if (pq_is_empty(q)) {
        fprintf(stderr, "Error: Attempted to dequeue from an empty queue.\n");
        exit(1);
    }

    Node *dequeueTree = q->list->tree;

    //rm the first ele w lowest weight
    ListElement *temp = q->list;
    q->list = q->list->next;
    free(temp);

    return dequeueTree;
}

//pq_print()

void pq_print(PriorityQueue *q) {
    assert(q != NULL);

    ListElement *e = q->list;
    int position = 1;

    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }

        node_print_tree(e->tree);
        e = e->next;
    }

    printf("=============================================\n");
}
