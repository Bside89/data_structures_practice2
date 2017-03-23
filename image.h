//
// Created by Blue on 29/02/2016.
//

#ifndef TP2_IMAGEM_H
#define TP2_IMAGEM_H


#include <stdint.h>
#include <stdio.h>


struct _pmg_img {
    size_t rows, cols;
    int maxgray;
    int **data;
};


typedef struct _pmg_img* Image;


static Image pgm_open_n_get(const char *filename);

static int ** pgm_reserve_matrix(size_t rows, size_t cols);

static void pgm_destroy_matrix(Image ipgm);

static int pgm_pixel_is_valid(int i, int j, int lim_x, int lim_y);

Image pgm_init(void);

void pgm_scan(const char *filename, Image *ipgm);

int pgm_get_maxgray(Image ipgm);

Image pgm_ccl(Image ipgm); // Função de rotulação de componentes conexas.

void pgm_close(Image *ipgm);


#endif //TP2_IMAGEM_H
