#ifndef __SIMPLE_LINKED_LIST_H__
#define __SIMPLE_LINKED_LIST_H__

typedef struct entry {
   int value;
   struct entry *next;
} entry_t;

void push(int value, entry_t **head);
int pop(entry_t **head);
int size(const entry_t *const head);
int back(const entry_t *const head);

#endif
