#include <stdlib.h>  // NULL and malloc are needed 
#include <assert.h> // assert is needed

#include "my_malloc.h"
#include "simple_linked_list.h"

void push(int value, entry_t **head) 
{ // add new entry at front 
   entry_t *new_entry = CheckedMalloc(sizeof(entry_t));
   new_entry->value = value; // set data 
   if (*head == NULL) { // first entry in the list
      new_entry->next = NULL; // reset the next 
   } else {
      new_entry->next = *head;
   }
   *head = new_entry; //update the head 
}

int pop(entry_t **head)
{
   assert(head != NULL && *head != NULL); // linked list must be non-empty
   entry_t *prev_head = *head; // save the current head
   int ret = prev_head->value;
   *head = prev_head->next;
   free(prev_head); // relase the memory for the popped entry
   return ret;
}

int size(const entry_t *const head)
{ // we do not attempt to modify the list
   int counter = 0;
   const entry_t *cur = head; // use pointer to const value 
   while (cur) { // or cur != NULL
      cur = cur->next;
      counter += 1;
   }
   return counter;
}

int back(const entry_t *const head)
{ 
   const entry_t *end = head;
   while (end && end->next) { 
      end = end->next;
   }
   assert(end); // we do not allow to call back on empty list
   return end->value;
}
