// Jason Kim jhk74

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/c/cs223/Hwk4/Deque.h"
//#include "Deque.h"



// The internal representation of the Deque ADT is a pair of stacks (the H
// stack and the T stack), each implemented using a headless, singly-linked
// list.  To add an item to the tail (head) of the Deque, push it onto the
// top of the T (H) stack.  To remove an item from the head of the Deque,
// pop it off the top of the H stack (but if the H stack is empty, first
// move items one at a time from the top of the T stack to the top of the H
// stack until the T stack is empty).
//
// This data structure requires one link per item rather than two as in the
// doubly-linked list implementation given in Aspnes' notes.  But while
// removing an item may not take constant time when the H stack is empty,
// the average time per operation for a sequence of operations that begins
// and ends with an empty Deque is constant.  (Why?)
typedef struct node {
    char * data;
    struct node *next;
} Node;

struct deque {
    struct node* H;
    struct node* T;
};

void freeNode(struct node ** Node)
{
    free((*Node)->data);
    (*Node)->data = NULL;
    (*Node)->next = NULL;
    free(*Node);
}

struct node * createN(char * s)
{
    struct node * n = (struct node *)malloc(sizeof(struct node));
    n->data = (char *)malloc(250 * sizeof(char));
    strcpy(n->data, s);
    n->next = NULL;
    return n;
}

// Implementation of createD()
bool createD (Deque *d) {
    if ((*d = malloc(sizeof(**d))) == NULL) {
        return false;
    }
    (*d)->H = NULL;
    (*d)->T = NULL;
    return true;
}


// Implementation of isEmptyD()
bool isEmptyD (Deque *d)
{
    return((*d)->H == NULL && (*d)->T == NULL);
}

// Implementation of addD()
bool addD (Deque *d, char *s)
{
    //struct node *temp =  (*d)->T;
    //if (temp == NULL) {
    //    return false;
    //}
    struct node * temp = createN(s);
    temp->next = (*d)->T;

    (*d)->T = temp;
    return true;

}


// Implementation of remD()
bool remD(Deque * d, char ** s) {
    if (isEmptyD(d))
    {
        *s = NULL;
        return false;
    }
    // transfer nodes from tail to head if head empty
    struct node *temp = NULL;
    if((*d)->H == NULL) {
        while((*d)->T != NULL) {
            temp = (*d)->T->next;
            pushD(d, (*d)->T->data);
            freeNode(&(*d)->T);
            (*d)->T = temp;
        }
        // reset temp
        temp = NULL;
    }
    //*s = (*d)->H->data;
    //struct node* newNode = (*d)->H;
    //(*d)->H = (*d)->H->next;

    if((*d)->H != NULL) {
        temp = (*d)->H;
        //strcpy(*s, temp->data);
        *s = (char *)malloc(250 * sizeof(char));
        strcpy(*s, temp->data);
        (*d)->H = temp->next;
        //free(temp->data);
        //free(temp);
        freeNode(&temp);
    }
    return true;
}


bool headD(Deque * d, char ** s)
{
    if (isEmptyD(d) || s == NULL) {
        return false;
    }
    struct node* temp = NULL;
    if((*d)->H == NULL) {
        while((*d)->T != NULL) {
            temp = (*d)->T->next;
            pushD(d, (*d)->T->data);
            freeNode(&(*d)->T);
            (*d)->T = temp;
        }
        temp = NULL;
    }
    *s = (char *)malloc(250 * sizeof(char));
    //*s = (*d)->H->data;
    strcpy(*s, (*d)->H->data);
    return true;

}

bool pushD(Deque * d, char * s)
{
    struct node* newNode = createN(s);
    if (newNode == NULL) {
        return false;
    }
    newNode->next = (*d)->H;
    (*d)->H = newNode;
    return true;
}

bool destroyD(Deque *d)
{
    if (*d == NULL) {
        return false;
    }
    struct node *temp = NULL;
    while ((*d)->H)
    {
        temp = (*d)->H->next;
        freeNode(&(*d)->H);
        (*d)->H->next = temp;
    }

    while((*d)->T) {
        temp = (*d)->T->next;
        freeNode(&(*d)->T);
        (*d)->T->next = temp;
    }
    temp = NULL;
    free(*d);
    // needed to set *d to NULL so that it would work!!!!!
    *d = NULL;
    return true;
}