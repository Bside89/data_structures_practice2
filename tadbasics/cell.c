//
// Created by Blue on 28/02/2016.
//

#include "cell.h"
#include "xcpt.h"
#include <stdio.h>
#include <stdlib.h>


/* F: Cria uma nova célula da lista encadeada.
 * */
static Cell * ic_alloc(const int val) {

    Cell *c = malloc(sizeof(Cell));

    if (c == NULL) // Alocação não deu certo?
        xcpt(ERROR_ALLOC);
    else {
        c->info = val;
        c->prev = c->next = NULL;
    }
    return c;
}


/* F: Verifica se a lista 'c' está vazia.
 * */
short ic_is_null(Cell *c) {
    return c == NULL;
}


/* F: Insere uma nova célula no início da lista 'c'.
 * */
Cell * ic_insert_begin(const int val, Cell **c) {

    Cell *it, *newcell = ic_alloc(val);

    it = get_begin(*c); // Garante a inserção no início.
    newcell->prev = NULL;
    newcell->next = it;
    if (it != NULL)
        it->prev = newcell;
    *c = newcell;

    return newcell;
}


/* F: Insere uma nova célula no fim da lista.
 * */
Cell * ic_insert_end(const int val, Cell *c) {

    if (ic_is_null(c)) return NULL;

    Cell *it = c, *newcell = ic_alloc(val);

    while (it->next != NULL) // Garante a inserção no fim.
        it = it->next;
    it->next = newcell;
    newcell->prev = it;
    newcell->next = NULL;
    return newcell;
}


/* F: Dado uma lista 'c' e um valor 'val' a ser buscado dentro da lista,
 * a função retorna o endereço de memória da célula contendo o valor.
 * Caso nenhum valor seja encontrado, a função retorna NULL.
 * */
Cell * ic_search(const int val, Cell *c) {

    if (c->info == val || ic_is_null(c))
        return c;
    return ic_search(val, c->next); // Analisa a sub-lista.
}


/* F: Remove uma célula de valor 'val' da lista 'c'.
 * */
void ic_remove(const int val, Cell **c) {

    Cell *removed = ic_search(val, *c);

    if (ic_is_null(removed)) // O valor não está na lista?
        return;
    if (!ic_is_null(removed->prev)) // O valor não está no início da lista?
        removed->prev->next = removed->next;
    else
        *c = removed->next;
    if (!ic_is_null(removed->next)) // O valor não está no fim da lista?
        removed->next->prev = removed->prev;
    free(removed);
}


/* F: Retorna a primeira célula (cabeça) de uma lista 'c'
 * */
Cell * get_begin(Cell *c) {

    if (ic_is_null(c) || ic_is_null(c->prev)) // A lista é vazia ou já é a primeira célula?
        return c;
    return get_begin(c->prev); // Percorre a lista reversamente.
}


/* F: Remove todas as células da lista 'c'.
 * */
void ic_remove_all(Cell **c) {

    if (ic_is_null(*c))
        return;
    ic_remove_all(&(*c)->next);
    free(*c); // Liberação de memória via backtracking.
    *c = NULL;
}
