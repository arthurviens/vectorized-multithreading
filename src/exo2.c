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

#include "exo2.h"


double vect_norm4(double *U, double a, double b, double c, double d, int n) {
    /* Declarations */
    int i;
    int L = 32;
    double total;

    __m256d *ptr_vec;
    __m256d *ptr;

    double *res, *vec;

    /* Initialisations */
    vec = malloc(4 * sizeof(double) + L);
    while (((long int)vec % L) != 0) {
        vec =(double*)((long int)vec + 1);
    }

    res = malloc(4 * sizeof(double) + L);
    while (((long int)res % L) != 0) {
        res =(double*)((long int)res + 1);
    }

    vec[0] = a*a; vec[1] = b*b; vec[2] = c*c; vec[3] = d*d;
    res[0] = 0; res[1] = 0; res[2] = 0; res[3] = 0;
    total = 0;

    ptr = (__m256d*)U;
    ptr_vec = (__m256d*)vec;
    
    for(i = 0; i < (n/4); i++, ptr++, U += 4) {
        _mm256_store_pd(res, _mm256_mul_pd(*ptr_vec, *ptr));
        total += sqrt(res[0] + res[1] + res[2] + res[3]);
    }
    
    return total;
}