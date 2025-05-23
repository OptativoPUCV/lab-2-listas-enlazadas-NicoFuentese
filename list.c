#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* newList = (List*) malloc(sizeof(List));
    if (newList == NULL) return NULL; // Verificar si la asignación de memoria falló

    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    
    return newList;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head; 
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) 
        return NULL;

    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) 
        return NULL;

    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;

    Node* newNode = createNode(data);
    if (newNode == NULL) return;

    newNode->next = list->head;

    if (list->head != NULL) {
        list->head->prev = newNode;
    } else {
        list->tail = newNode;
    }

    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return;

    Node* newNode = createNode(data);
    if (newNode == NULL) return;

    newNode->next = list->current->next;
    newNode->prev = list->current;

    if (list->current->next != NULL) {
        list->current->next->prev = newNode;
    } else {
        list->tail = newNode;
    }

    list -> current -> next = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    Node* temp = list->current;
    void* data = temp->data;

    if (list->current == list->head) {
        list->head = list->current->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    } else {
        list->current->prev->next = list->current->next;
    }

    if (list->current == list->tail) {
        list->tail = list->current->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    } else {
        list->current->next->prev = list->current->prev;
    }

    list->current = list->current->next;

    free(temp);

    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}