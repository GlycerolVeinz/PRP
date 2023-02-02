#include <stdlib.h>  // NULL and malloc are needed 
#include <stdbool.h>
#include <string.h> // string operations are needed
#include <assert.h> // assert is needed

#include "my_malloc.h"
#include "linked_list-str.h"

/* 
 * static modificator at function make the function visible only
 * inside the current module, i.e., linked_list.c
 * This is useful for helper functions
 */ 
static entry_t* allocate_entry(const char *value);
static void free_entry(entry_t *entry);

// - function ----------------------------------------------------------------
void free_list(linked_list_t *list) 
{
   if (list) {
      entry_t *cur = list->head;
      while (cur) {
         entry_t *prev = cur;
         cur = cur->next;
         free_entry(prev);
      }
   }
}

// - function ----------------------------------------------------------------
void push(const char *value, linked_list_t *list)
{ // add new entry at front 
   assert(list);
   entry_t *new_entry = allocate_entry(value);
   if (list->head) { // an entry already in the list
      new_entry->next = list->head;
   } else { //list is empty
      new_entry->next = NULL; // reset the next 
   }
   list->head = new_entry; //update the head 
}

// - function ----------------------------------------------------------------
char* pop(linked_list_t *list)
{
   assert(list && list->head); // linked list must be non-empty
   entry_t *prev_head = list->head; // save the current head
   char* ret = prev_head->value;
   list->head = prev_head->next;
   prev_head->value = NULL; // avoid free 
   free_entry(prev_head); // relase the memory for the popped entry
   return ret;
}

// - function ----------------------------------------------------------------
int indexOf(const char *value, const linked_list_t *list)
{
   int counter = 0;
   const entry_t *cur = list->head;
   bool found = false;
   while (cur && !found) {
      found = strcmp(cur->value, value) == 0;
      cur = cur->next;
      counter += 1;
   }
   return found ? counter - 1 : -1;
}

// - helper local function ---------------------------------------------------
static entry_t* allocate_entry(const char *value)
{
   entry_t *entry = CheckedMalloc(sizeof(entry_t));
   if (value) {
      entry->value = CheckedMalloc(sizeof(char)*(strlen(value) + 1));
      strcpy(entry->value, value); // we assume value is properly allocated
   } else {
      entry->value = NULL;
   }
   return entry;
}

// - helper local function ---------------------------------------------------
static void free_entry(entry_t *entry)
{
   if (entry) {
      if (entry->value) {
         free(entry->value);
      }
      free(entry);
   }
}
