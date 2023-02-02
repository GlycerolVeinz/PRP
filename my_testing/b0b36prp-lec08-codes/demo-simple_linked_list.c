#include <stdio.h>   // printf is needed
#include <stdlib.h>  // NULL is needed

#include "simple_linked_list.h"

void print(const entry_t *const head)
{
   const entry_t *cur = head; // set the cursor to head
   while (cur != NULL) {
      printf("%i%s", cur->value, cur->next ? " " : "\n");
      cur = cur->next; // move in the linked list
   }
}

int main(int argc, char *argv[]) 
{
   entry_t *head;
   head = NULL; // initialization is important 

   push(17, &head);
   push(7, &head);

   printf("List: ");
   print(head);
   push(5, &head);

   printf("\nList size: %i\n", size(head));
   printf("Last entry: %i\n\n", back(head));

   printf("List: ");
   print(head);

   push(13, &head);
   push(11, &head);
   pop(&head);

   printf("List: ");
   print(head);

   printf("\nCleanup using pop until head is not empty\n");
   while (head != NULL) {
      const int value = pop(&head);
      printf("Popped value %i\n", value);
   }
   printf("List size: %i\n", size(head));
   printf("Last entry: %i\n", back(head));
   return 0;
}
