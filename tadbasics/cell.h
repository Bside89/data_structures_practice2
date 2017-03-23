//
// Created by Blue on 28/02/2016.
//

#ifndef TP2_CELL_H
#define TP2_CELL_H


struct _cell {
    int info;
    struct _cell *prev;
    struct _cell *next;
};


typedef struct _cell Cell;


static Cell * ic_alloc(const int val);

short ic_is_null(Cell *source);

Cell * ic_insert_begin(const int val, Cell **target);

Cell * ic_insert_end(const int val, Cell *target);

Cell * ic_search(const int val, Cell *source);

void ic_remove(const int val, Cell **target);

Cell * get_begin(Cell *target);

void ic_remove_all(Cell **target);


#endif //TP2_CELL_H
