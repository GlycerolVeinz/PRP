
#include <stdlib.h>  // NULL and malloc are needed 
#include <stdbool.h>
#include <assert.h> // assert is needed

#include "my_malloc.h"
#include "linked_list.h"

// - function ----------------------------------------------------------------
void free_list(linked_list_t *list) 
{
   if (list) {
      entry_t *cur = list->head;
      while (cur) {
         entry_t *prev = cur;
         cur = cur->next;
         free(prev);
      }
   }
}

// - function ----------------------------------------------------------------
void push(int value, linked_list_t *list)
{ // add new entry at front 
   assert(list);
   entry_t *new_entry = CheckedMalloc(sizeof(entry_t));
   new_entry->value = value; // set data 
   if (list->head) { // an entry already in the list
      new_entry->next = list->head;
   } else { //list is empty
      new_entry->next = NULL; // reset the next 
      list->tail = new_entry; //1st entry is the end
   }
   list->head = new_entry; //update the head 
   list->counter += 1;
}

// - function ----------------------------------------------------------------
int pop(linked_list_t *list)
{
   assert(list && list->head); // linked list must be non-empty
   entry_t *prev_head = list->head; // save the current head
   int ret = prev_head->value;
   list->head = prev_head->next;
   list->counter -= 1;
   free(prev_head); // release the memory for the popped entry
   if (list->head == NULL) { // end has been popped
      list->tail = NULL;
   }
   return ret;
}

// - function ----------------------------------------------------------------
int size(const linked_list_t *const list)
{ // we do not attempt to modify the list; hence we are using const, const
   assert(list);
   return list->counter;
}

// - function ----------------------------------------------------------------
int back(const linked_list_t *const list)
{
   assert(list && list->tail); // we do not allow to call back on empty list
   return list->tail->value;
}

// - function ----------------------------------------------------------------
void pushEnd(int value, linked_list_t *list)
{
   assert(list);
   entry_t *new_entry = CheckedMalloc(sizeof(entry_t));
   new_entry->value = value; // set data 
   new_entry->next = NULL; // set the next
   if (list->tail == NULL) { //adding the 1st entry
      list->head = list->tail = new_entry;
   } else {
      list->tail->next = new_entry; //update the current tail 
      list->tail = new_entry;
   }
   list->counter += 1;
}

// - function ----------------------------------------------------------------
int popEnd(linked_list_t *list)
{
   assert(list && list->head);
   entry_t *end= list->tail; // save the end
   if (list->head == list->tail) { // the last entry is
      list->head = list->tail = NULL; // removed
   } else { // there is also penultimate entry
      entry_t *cur = list->head; // that needs to be
      while (cur->next != end) { // updated (its next 
         cur = cur->next; // pointer to the next entry
      }
      list->tail = cur;
      list->tail->next = NULL; //the tail does not have next
   }
   int ret = end->value;
   free(end);
   list->counter -= 1;
   return ret;
}

// - helper local function ---------------------------------------------------
/* 
 * static modificator at function make the function visible only
 * inside the current module, i.e., linked_list.c
 */ 
static entry_t* getEntry(int index, const linked_list_t *list)
{ // here, we assume index >= 0
   entry_t *cur = list->head;
   int i = 0;
   while (i < index && cur != NULL && cur->next != NULL) {
      cur = cur->next;
      i += 1;
   }
   return cur; //return entry at the index or the last entry
}

// - function ----------------------------------------------------------------
void insertAt(int value, int index, linked_list_t *list)
{
   assert(list);
   if (index < 0) { return; } // only positive position
   if (index == 0) { push(value, list); return; }
   entry_t *new_entry = CheckedMalloc(sizeof(entry_t));
   new_entry->value = value; // set data 
   entry_t *entry = getEntry(index - 1, list);
   if (entry != NULL) { // entry can be NULL for the 1st entry (empty list), i.e., for the case list->head == entry == NULL
      new_entry->next = entry->next;
      entry->next = new_entry;
   }
   if (entry == list->tail) {
      list->tail = new_entry;
   }
   list->counter += 1;
}

// - function ----------------------------------------------------------------
entry_t* getAt(int index, const linked_list_t *const list)
{
   if (index < 0 || list == NULL || list->head == NULL) { return NULL; } // check the arguments first
   entry_t* cur = list->head;
   int i = 0;
   while (i < index && cur != NULL && cur->next != NULL) {
      cur = cur->next;
      i++;
   }
   return (cur != NULL && i == index) ? cur : NULL;
}

// - function ----------------------------------------------------------------
void removeAt(int index, linked_list_t *list)
{
   if (index < 0 || list == NULL || list->head == NULL) { return; } // check the arguments first
   if (index == 0) {
      pop(list); // call the pop function to handle remove head
   } else {
      entry_t *entry_prev = getEntry(index - 1, list);
      entry_t *entry = entry_prev->next; //entry_prev is not NULL because of the return at the first line 
      if (entry != NULL) { //handle connection
         entry_prev->next = entry_prev->next->next;
      }
      if (entry == list->tail) {
         list->tail = entry_prev;
      }
      free(entry);
      list->counter -= 1;
   }
}

// - function ----------------------------------------------------------------
int indexOf(int value, const linked_list_t *const list)
{
   int counter = 0;
   const entry_t *cur = list->head;
   bool found = false;
   while (cur && !found) {
      found = cur->value == value;
      cur = cur->next;
      counter += 1;
   }
   return found ? counter - 1 : -1;
}
