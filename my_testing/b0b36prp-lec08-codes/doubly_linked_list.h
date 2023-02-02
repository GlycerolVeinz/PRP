#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

typedef struct dll_entry {
   int value;
   struct dll_entry *prev;
   struct dll_entry *next;
} dll_entry_t;

typedef struct {
   dll_entry_t *head;
   dll_entry_t *tail;
} doubly_linked_list_t;

void free_dll(doubly_linked_list_t *list);

void push_dll(int value, doubly_linked_list_t *list);

void print_dll(const doubly_linked_list_t *list);

void printReverse(const doubly_linked_list_t *list);

#endif

