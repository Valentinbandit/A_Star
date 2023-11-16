#ifndef ASTAR_LINKEDLIST_H
#define ASTAR_LINKEDLIST_H

#include <stdbool.h>
#include "graphElements.h"

typedef struct ListCell {
    struct ListCell *previous, *next;
    Node data;
} ListCell;

typedef struct List {
    ListCell *first, *last;
} List;
bool Contains(List *list, Node *data);
void addToListSpec(List *list, Node *newData, ListCell **temp);
void addToList(List *list, Node *newData);
int Count(List *list);
void removeFromList(List *list, ListCell *toRemove);
void DeleteList(List *list);


#endif //ASTAR_LINKEDLIST_H
