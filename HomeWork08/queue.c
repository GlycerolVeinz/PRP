#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ERR_CRQ 100
#define ERR_CRA 101
#define ERR_REA 102
#define ERR_PSH 103
#define Starting_Capacity 10

void err_msg(int err_type)
{
    fprintf(stderr, "Error: ");

    switch (err_type)
    {
    case ERR_CRQ:
        fprintf(stderr, "failed to malloc new queue.");
        break;
    case ERR_CRA:
        fprintf(stderr, "failed to malloc new arr for queue.");
        break;
    case ERR_PSH:
        fprintf(stderr, "trying to push a null pointer to queue.");
    }

    exit(err_type);
}

queue_t *create_queue(int capacity)
{
    // printf("\ncapacity = %d\n", capacity);
    // alloc everything needed
    queue_t *cir_que;
    cir_que = malloc(sizeof(queue_t));
    if (!cir_que)
    {
        err_msg(ERR_CRQ);
    }
    
    cir_que->arr = calloc(capacity, sizeof(void*));
    if (!(cir_que->arr))
    {
        err_msg(ERR_CRA);
    }

    // initialise queue variables
    cir_que->capacity = capacity;
    cir_que->size = 0;
    cir_que->front = -1;
    cir_que->end = -1;

    return cir_que;
}

void delete_queue(queue_t *queue)
{
    // free all malloced space
    free(queue->arr);
    free(queue);
}

bool is_full(queue_t *queue)
{
    bool ret = false;
    if ((queue->size == queue->capacity) && queue->size != 0)
    {
        ret = true;
    }
    return ret;
}

bool is_empty(queue_t *queue)
{
    bool ret = false;
    if (queue->size == 0)
    {
        ret = true;
    }
    return ret;
}

bool push_to_queue(queue_t *queue, void *data)
{
    bool ret = false;

    // if first element
    if ((is_empty(queue)) && (queue->front == -1))
    {
        queue->front = 0;
        queue->end = 0;
        queue->arr[queue->end] = data;
        queue->size += 1;
        ret = true;
    }
    // if full
    else if (is_full(queue))
    {
        ret = false;
    }
    // if pointer to data is invalid
    // (could ruin queue functions)
    else if (!data)
    {
        err_msg(ERR_PSH);
    }
    // default state
    else
    {
        queue->end = (queue->end + 1) % (queue->capacity);
        queue->arr[queue->end] = data;
        queue->size += 1;
        ret = true;
    }

    return ret;
}

void *pop_from_queue(queue_t *queue)
{
    void *popped = NULL;

    // return null on empty
    if (is_empty(queue))
    {
        popped = NULL;
    }
    // else return front, and change front, decrese size
    else
    {
        popped = queue->arr[queue->front];
        queue->arr[queue->front] = NULL;
        queue->front = (queue->front + 1) % (queue->capacity);
        queue->size -= 1;
        if(is_empty(queue))
        {
            queue->front = -1;
            queue->end = -1;
        }
    }

    return popped;
}

void *get_from_queue(queue_t *queue, int idx)
{
    void *gotted = NULL;
    int position = 0;

    // if is empty or idx is weird return null
    if ((idx < 0) || is_empty(queue) || (idx >= queue->capacity))
    {
        gotted = NULL;
    }
    // else return position in array
    else
    {
        position = (queue->front + idx) % (queue->capacity);
        gotted = queue->arr[position];
    }

    return gotted;
}

int get_queue_size(queue_t *queue)
{
    return (queue->size);
}
