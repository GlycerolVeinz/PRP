#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct entry {
   int value;
   struct entry *next;
} entry_t;

typedef struct {
   entry_t *head;
   entry_t *tail;
   int counter;
} linked_list_t;

void free_list(linked_list_t *list);

void push(int value, linked_list_t *list);
int pop(linked_list_t *list);
int size(const linked_list_t *const list);
int back(const linked_list_t *const list);

void pushEnd(int value, linked_list_t *list);
int popEnd(linked_list_t *list);

void insertAt(int value, int index, linked_list_t *list);

entry_t* getAt(int index, const linked_list_t *const list);
void removeAt(int index, linked_list_t *list);

int indexOf(int value, const linked_list_t *const list);
#endif
