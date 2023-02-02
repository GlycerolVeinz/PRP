#include <stdio.h> // printf is needed
#include <stdlib.h>  // NULL and malloc are needed 
#include <stdbool.h>
#include <assert.h> // assert is needed

#include "my_malloc.h"
#include "doubly_linked_list.h"

static dll_entry_t* allocate_dll_entry(int value);
static void insert_dll(int value, dll_entry_t *cur);

// - function ----------------------------------------------------------------
void free_dll(doubly_linked_list_t *list)
{
   if (list) {
      dll_entry_t *cur = list->head;
      while (cur) {
         dll_entry_t *prev = cur;
         cur = cur->next;
         free(prev);
      }
   }
}

// - function ----------------------------------------------------------------
void push_dll(int value, doubly_linked_list_t *list)
{
   assert(list);
   dll_entry_t *new_entry = allocate_dll_entry(value);
   if (list->head) { // an entry already in the list
      new_entry->next = list->head; // connect new -> head
      list->head->prev = new_entry; // connect new <- head
   } else { //list is empty
      list->tail = new_entry;
   }
   list->head = new_entry; //update the head 
}

// - function ----------------------------------------------------------------
void print_dll(const doubly_linked_list_t *list)
{
   if (list && list->head) {
      dll_entry_t *cur = list->head;
      while (cur) {
         printf("%i%s", cur->value, cur->next ? " " : "\n");
         cur = cur->next;
      }
   }
}

// - function ----------------------------------------------------------------
void printReverse(const doubly_linked_list_t *list)
{
   if (list && list->tail) {
      dll_entry_t *cur = list->tail;
      while (cur) {
         printf("%i%s", cur->value, cur->prev? " " : "\n");
         cur = cur->prev;
      }
   }
}

// - helper local function ---------------------------------------------------
dll_entry_t* allocate_dll_entry(int value)
{
   dll_entry_t *new_entry = CheckedMalloc(sizeof(dll_entry_t));
   new_entry->value = value;
   new_entry->next = NULL;
   new_entry->prev = NULL;
   return new_entry;
}

// - helper local function ---------------------------------------------------
// Insert value before the cur entry
void insert_dll(int value, dll_entry_t *cur)
{
   assert(cur);
   dll_entry_t *new_entry = allocate_dll_entry(value);
   new_entry->next = cur;
   new_entry->prev = cur->prev;
   if (cur->prev != NULL) {
      cur->prev->next = new_entry;
   }
   cur->prev = new_entry;
}

