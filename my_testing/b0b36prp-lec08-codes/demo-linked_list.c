#include "linked_list.h"

#include <stdio.h>   // printf is needed
#include <stdlib.h>  // NULL is needed

void print(const linked_list_t *const list)
{
   if (list) {
      const entry_t *cur = list->head; 
      while (cur != NULL) {
         printf("%u%s", cur->value, cur->next ? " " : "\n");
         cur = cur->next; // move in the linked list
      }
   }
}

int main(int argc, char *argv[]) 
{
   linked_list_t list = { NULL, NULL, 0}; // initialization is important 
   linked_list_t *lst = &list;

   push(17, lst); push(7, lst);

   printf("List: ");
   print(lst);
   push(5, lst);

   printf("\nList size: %u\n", size(lst));
   printf("Last entry: %u\n\n", back(lst));

   printf("List: ");
   print(lst);

   push(13, lst);
   push(11, lst);
   printf("Push 13 and 11\n");
   printf("Pop %u\n", pop(lst));
   printf("Pop last entry: %u\n", popEnd(lst));
   printf("Push end 23\n");
   pushEnd(23, lst);

   printf("List: ");
   print(lst);

   printf("\nCleanup using pop until size(lst) > 0\n");
   while (size(lst) > 0) {
      const int value = pop(lst);
      printf("Popped value %u\n", value);
   }
   printf("List size: %u\n", size(lst));
   //  printf("Last entry: %u\n", back(lst));
   return 0;
}
