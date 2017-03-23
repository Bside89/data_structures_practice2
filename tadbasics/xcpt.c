//
// Created by Blue on 11/03/2016.
//

#include "xcpt.h"
#include <stdlib.h>
#include <stdio.h>



/* F: Exibe uma mensagem 'message' no console de erro e encerra o programa.
 * */
int xcpt(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}
