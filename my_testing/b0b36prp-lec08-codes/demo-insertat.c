#include "linked_list.h"

#include <stdio.h>   // printf is needed
#include <stdlib.h>  // NULL is needed

void print(const linked_list_t *const list)
{
   if (list) {
      const entry_t *cur = list->head; 
      while (cur != NULL) {
         printf("%i%s", cur->value, cur->next ? " " : "\n");
         cur = cur->next; // move in the linked list
      }
   }
}

int main(int argc, char *argv[]) 
{
   linked_list_t list = { NULL, NULL, 0 }; // initialization is important 
   linked_list_t *lst = &list;

   push(10, lst); push(5, lst); push(17, lst); push(7, lst); push(21, lst);
   print(lst);

   insertAt(55, 2, lst);
   print(lst);

   insertAt(0, 0, lst);
   print(lst);

   insertAt(100, 10, lst);
   print(lst);

   free_list(lst);
   return 0;
}
