//
// Created by Blue on 28/02/2016.
//

#include "queue.h"
#include "xcpt.h"
#include <stdlib.h>
#include <stdio.h>


#define ERROR_EMPTY_QUEUE "Error: Queue is empty."


/* Inicializa uma fila vazia.
 * */
Queue q_init(void) {
    Queue f = malloc(sizeof(struct _int_queue));
    f->begin = f->end = NULL;
    return f;
}


/* Verifica se uma fila 'f' está ou não vazia.
 * */
int q_is_empty(Queue f) {
    return f == NULL || f->begin == NULL;
}


/* Enfileira um elemento 'val' na fila 'f'.
 * */
void q_enqueue(const int val, Queue f) {

    if (q_is_empty(f)) {
        ic_insert_begin(val, &(f->begin));
        f->end = f->begin;
    } else
        f->end = ic_insert_end(val, f->end);
}


/* Desenfileira um elemento da fila 'f'.
 * */
int q_dequeue(Queue f) {

    if (q_is_empty(f))
        return xcpt(ERROR_EMPTY_QUEUE);
    int val = f->begin->info;
    ic_remove(val, &(f->begin));
    if (ic_is_null(f->begin))
        f->end = f->begin;
    return val;
}


/* Retorna o primeiro elemento duma fila 'f'.
 * */
int q_get_front(Queue f) {
    if (q_is_empty(f))
        return xcpt(ERROR_EMPTY_QUEUE);
    return f->begin->info;
}


int q_get_back(Queue f) {
    if (q_is_empty(f))
        return xcpt(ERROR_EMPTY_QUEUE);
    return f->end->info;
}


size_t q_size(Queue f) {
    Cell *it;
    size_t counter = 0;
    for (it = f->begin; it != NULL; it = it->next)
        counter++;
    return counter;
}


void q_print(Queue f) {

    Cell *it;
    putchar('(');
    if (q_is_empty(f))
        putchar(' ');
    else for (it = f->begin; it != NULL; it = it->next) {
        printf("%d", it->info);
        if (it->next != NULL)
            printf(", ");
    }
    puts(")");
}


void q_destroy(Queue *f) {
    ic_remove_all(&((*f)->begin));
    free(*f);
    *f = NULL;
}
