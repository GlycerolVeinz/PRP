#ifndef __LINKED_LIST_STR_H__
#define __LINKED_LIST_STR_H__

typedef struct entry {
   char* value;
   struct entry *next;
} entry_t;

typedef struct {
   entry_t *head;
} linked_list_t;

void free_list(linked_list_t *list);

void push(const char *value, linked_list_t *list);

/* 
 * return the string, that must be
 * explicitely delete outside the pop function
 */ 
char* pop(linked_list_t *list);

int indexOf(const char *value, const linked_list_t *list);

#endif
