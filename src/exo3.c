/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fonctions pour l'exercice 2
 */
#include <pmmintrin.h>
#include <immintrin.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exo3.h"

double norm4Par(double *U, double a, double b, double c, double d, int n, int nb_threads) {
    struct data_thread Dthread;
    Dthread.U = U;
    Dthread.a = a;
    Dthread.b = b;
    Dthread.c = c;
    Dthread.d = d;
    Dthread.n = n;
    printf("Struct data_thread : a = %f, b = %f, c = %f, d = %f, n = %d\n", 
                Dthread.a, Dthread.b, Dthread.c, Dthread.d, Dthread.n);

    return 0;
}