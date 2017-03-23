#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"


#define N 100


// Funções auxiliares:

void fix_string(char *str);

void flush(void);


int main(void) {

    Image I = NULL, J = NULL;
    int n;
    char buffer[N];

    scanf("%d", &n);
    flush();
    while (n > 0) {
        fgets(buffer, N, stdin);
        fix_string(buffer);
        pgm_scan(buffer, &I);
        J = pgm_ccl(I);
        printf("%d\n", pgm_get_maxgray(J));
        pgm_close(&I);
        pgm_close(&J);
        n--;
    }
    getchar();
    return EXIT_SUCCESS;
}


void fix_string(char *str) {
    int i = strlen(str) - 1;
    if (str[i] == '\n') str[i] = '\0';
}


void flush(void) {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
