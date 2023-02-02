#include "doubly_linked_list.h"

#include <stdio.h>

int main(void)
{
   doubly_linked_list_t list = { NULL, NULL }; // initialization is important 
   doubly_linked_list_t *lst = &list;

   push_dll(17, lst); push_dll(93, lst); 
   push_dll(79, lst); push_dll(11, lst);

   printf("Regular print: ");
   print_dll(lst);

   printf("Revert print: ");
   printReverse(lst);

   free_dll(lst);
   return 0;
}

