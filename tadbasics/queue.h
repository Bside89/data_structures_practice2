//
// Created by Blue on 28/02/2016.
//

#ifndef TP2_QUEUE_H
#define TP2_QUEUE_H


#include "cell.h"
#include <stddef.h>


struct _int_queue {
    Cell *begin;
    Cell *end;
};


typedef struct _int_queue * Queue;


Queue q_init(void);

int q_is_empty(Queue source);

void q_enqueue(const int val, Queue target);

int q_dequeue(Queue target);

int q_get_front(Queue source);

int q_get_back(Queue source);

size_t q_size(Queue source);

void q_print(Queue source);

void q_destroy(Queue *target);


#endif //TP2_QUEUE_H
