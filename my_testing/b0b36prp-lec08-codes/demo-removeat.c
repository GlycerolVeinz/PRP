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

void removeAndPrint(int index, linked_list_t *lst)
{
   entry_t *e = getAt(index, lst);
   printf("Remove entry at %i (%i)\n", index, e ? e->value : -1);
   removeAt(index, lst);
   print(lst);
}

int main(int argc, char *argv[]) 
{
   linked_list_t list = { NULL, NULL, 0 }; // initialization is important 
   linked_list_t *lst = &list;

   push(10, lst); push(5, lst); push(17, lst); push(7, lst); push(21, lst);
   print(lst);

   removeAndPrint(3, lst);
   removeAndPrint(3, lst);
   removeAndPrint(0, lst);

   free_list(lst);
   return 0;
}
