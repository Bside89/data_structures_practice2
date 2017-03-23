//
// Created by Blue on 29/02/2016.
//

#include "image.h"
#include "tadbasics/queue.h"
#include "tadbasics/xcpt.h"
#include <stdlib.h>


#define PGM_NOT_FOUND "Arquivo não existe."


/* Inicializa uma variável do tipo Image.
 * */
Image pgm_init(void) {
    Image ipgm = malloc(sizeof(struct _pmg_img));
    ipgm->rows = ipgm->cols = 0;
    ipgm->data = NULL;
    return ipgm;
}


/* Reserva uma matriz 'rows' x 'cols' de valoes inteiros dos pixels
 * da imagem.
 * */
static int ** pgm_reserve_matrix(size_t rows, size_t cols) {
    size_t i;
    int **mat = calloc(rows, sizeof(int*));
    for (i = 0; i < rows; i++)
        mat[i] = calloc(cols, sizeof(int));
    return mat;
}


/* Desaloca uma matriz da memória.
 * */
static void pgm_destroy_matrix(Image ipgm) {
    int i;
    for (i = 0; i < ipgm->rows; i++)
        free(ipgm->data[i]);
    free(ipgm->data);
    ipgm->data = NULL;
}


/* Abre um arquivo de nome "'filename'.pgm" para leitura
 * e captura os dados do arquivo para o TAD Image.
 * */
static Image pgm_open_n_get(const char *filename) {

    Image ipgm = pgm_init();
    FILE* pgmstream = fopen(filename, "r"); // Obtém a stream de dados.
    char buffer[4];
    int i, j;

    fgets(buffer, sizeof(buffer) - 1, pgmstream);
    fscanf(pgmstream, "%u", &(ipgm->cols));
    fscanf(pgmstream, "%u", &(ipgm->rows));
    fscanf(pgmstream, "%d", &(ipgm->maxgray));
    ipgm->data = pgm_reserve_matrix(ipgm->rows, ipgm->cols);
    for (i = 0; i < ipgm->rows; i++)
        for (j = 0; j < ipgm->cols; j++)
            fscanf(pgmstream, "%d", &ipgm->data[i][j]);
    fclose(pgmstream);
    return ipgm;
}


/* Retorna o valor de maxgray de uma imagem 'ipgm'.
 * */
int pgm_get_maxgray(Image ipgm) {
    if (ipgm == NULL)
        return xcpt(PGM_NOT_FOUND);
    return ipgm->maxgray;
}


/* Lê um arquivo pgm e aloca na TAD Image 'ipgm'.
 * */
void pgm_scan(const char *filename, Image *ipgm) {
    Image p = pgm_open_n_get(filename);
    if (*ipgm != NULL)
        pgm_close(ipgm);
    *ipgm = p;
}


/* Recebe uma imagem binária 'I' e devolve uma imagem em tons de cinza 'J'
 * com todas as componentes binárias devidamente rotuladas
 * */
Image pgm_ccl(Image I) {

    if (I == NULL) return NULL;

    int i, j, m, n, label = 0, Px, Py;
    Image J = pgm_init();
    Queue Fx = q_init(), Fy = q_init();

    J->rows = I->rows;
    J->cols = I->cols;
    J->data = pgm_reserve_matrix(J->rows, J->cols);
    for (i = 0; i < I->rows; i++) {
        for (j = 0; j < I->cols; j++) {
            if (I->data[i][j] != 0 && J->data[i][j] == 0) {
                J->data[i][j] = ++label;
                q_enqueue(i, Fx);
                q_enqueue(j, Fy);
                while (!q_is_empty(Fx) && !q_is_empty(Fy)) { // Sai do laço quando rotular o componente.
                    Px = q_dequeue(Fx);
                    Py = q_dequeue(Fy);
                    for (m = Px - 1; m <= Px + 1; m++) { // Verifica os vizinhos-8 de (i, j).
                        for (n = Py - 1; n <= Py + 1; n++) {
                            if (!pgm_pixel_is_valid(m, n, I->rows, I->cols))
                                continue;
                            if (I->data[m][n] != 0 && J->data[m][n] == 0) {
                                J->data[m][n] = J->data[i][j];
                                q_enqueue(m, Fx);
                                q_enqueue(n, Fy);
                            }
                        }
                    }
                }
            }
        }
    }
    J->maxgray = label;
    q_destroy(&Fx);
    q_destroy(&Fy);

    return J;
}


/* Verifica se o pixel P(i, j) está dentro da matriz, que vai de 0 até
 * os limites 'lim_x' e 'lim_y' especificados.
 * */
int static pgm_pixel_is_valid(int i, int j, int lim_x, int lim_y) {
    return i >= 0 && j >= 0 && i < lim_x && j < lim_y;
}


/* Fecha o arquivo de imagem e desaloca qualquer dado alocado da memória.
 * */
void pgm_close(Image *ipgm) {
    pgm_destroy_matrix(*ipgm);
    free(*ipgm);
    *ipgm = NULL;
}
