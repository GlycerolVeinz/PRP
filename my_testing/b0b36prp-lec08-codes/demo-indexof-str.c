#include "linked_list-str.h"

#include <stdio.h>   // printf is needed
#include <stdlib.h>  // NULL is needed

void print(const linked_list_t *const list)
{
   if (list) {
      const entry_t *cur = list->head; 
      while (cur != NULL) {
         printf("%s%s", cur->value, cur->next ? " " : "\n");
         cur = cur->next; // move in the linked list
      }
   }
}

int main(int argc, char *argv[]) 
{
   linked_list_t list = { NULL }; // initialization is important 
   linked_list_t *lst = &list;

   push("FEE", lst); push("CTU", lst); push("PRP", lst); push("Lecture09", lst);
   print(lst);

   char *values[] = { "PRP", "Fee" };
   for (int i = 0; i < 2; ++i) {
      printf("Index of (%s) is %2i\n", values[i], indexOf(values[i],lst));
   }

   char *str = pop(lst);
   // printf("Popped value \"%s\"\n", pop(lst)); // Note, using this will cause memory leakage since we lost the address value to free the memory!!!
   printf("Popped value \"%s\"\n", str);
   printf("String of the popped value is at address %p\n", str);
   printf("Due to selected implementation the memory must be explicitely deallocated\n");
   free(str);

   free_list(lst); // cleanup !!!
   return 0;
}
