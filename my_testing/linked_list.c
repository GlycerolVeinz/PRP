#include <stdio.h>
#include <stdlib.h>

typedef struct list_entry
{
    int data;
    int index;
    struct list_entry *next;
} entry_type;

typedef struct
{
    entry_type *head;
    entry_type *tail;
    int counter;
} ll_type;

void *CheckedMalloc(size_t size)
{
    void *ret = malloc(size);
    if (!ret)
    {
        fprintf(stderr, "Malloc failed!\n");
        exit(100);
    }
    return ret;
}

void push(ll_type *where_to, int what_int)
{
    entry_type *new_input = CheckedMalloc(sizeof(entry_type));
    new_input->data = what_int;
    new_input->index = 0;

    if (where_to->head == NULL)
    {
        where_to->head = new_input;
        where_to->tail = new_input;
        new_input->next = NULL;
    }
    else
    {
        new_input->next = where_to->head;
        where_to->head = new_input;
    }

    where_to->counter++;
}



void append(ll_type *where_to, int what_int)
{
    entry_type *new_input = CheckedMalloc(sizeof(entry_type));
    new_input->data = what_int;
    new_input->index = where_to->counter;

    if (where_to->head == NULL)
    {
        where_to->head = new_input;
        where_to->tail = new_input;
        new_input->next = NULL;
    }
    else
    {
        new_input->next = NULL;
        where_to->tail->next = new_input;
        where_to->tail = new_input;
    }

    where_to->counter++;
}

int main(int argc, char const *argv[])
{

    ll_type *my_list = CheckedMalloc(sizeof(ll_type));
    entry_type *input = CheckedMalloc(sizeof(entry_type));

    int inputed_num = -1;
    char operator= getchar();
    while (inputed_num != 0)
    {
        if (!scanf("%d", &inputed_num))
        {
            fprintf(stderr, "Scanf failed\n");
            exit(101);
        }
        if (inputed_num != 0)
        {
            printf("you have inputed %d\n", inputed_num);
            switch (operator)
            {
            case '+':
                append(my_list, inputed_num);
                break;
            case '-':
                push(my_list, inputed_num);
                break;
        
            default:
                fprintf(stderr, "Something went wrong with operator sign\n");
                free(my_list);
                free(input);
                exit(102);
            }
        }
        else
        {
            printf("exiting...\n");
        }
        break;
    }

    printf("head: %p, head data: %d, tail data %d, counter: %d\n", my_list->head, my_list->head->data, my_list->tail->data, my_list->counter);

    free(my_list);
    free(input);
    exit(0);
}
