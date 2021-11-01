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

void test_permute() {
    __m256d vec1;
    __m256d vec2;

    vec1[0] = 0; vec1[1] = 2; vec1[2] = 4; vec1[3] = 6;
    
    vec2 = _mm256_permute4x64_pd(vec1, 0b11011000);
    
    printf("Vec1 : %f, %f, %f, %f \nVec2 : %f, %f, %f, %f\n",
    vec1[0], vec1[1], vec1[2], vec1[3], vec2[0], vec2[1], vec2[2], vec2[3]);

}


double vect_norm4(double *U, double a, double b, double c, double d, int n) {
    /* Declarations */
    int i;
    double total;

    __m256d carres;
    __m256d vec1;
    __m256d vec12;
    __m256d vec2;
    __m256d vec3;
    __m256d vec34;
    __m256d vec4;
    __m256d vecper1;
    __m256d vecper2;
    __m256d vectot;
    
    __m256d *ptr;
    __m256d res;

    /* Initialisations */

    carres[0] = a*a; carres[1] = b*b; carres[2] = c*c; carres[3] = d*d;
    total = 0;

    ptr = (__m256d*)U;
    
    for(i = 0; i < (n/4); i += 4, ptr += 4, U += 16) {
        vec1 = _mm256_mul_pd(carres, *ptr);
        vec2 = _mm256_mul_pd(carres, *(ptr+1));
        vec3 = _mm256_mul_pd(carres, *(ptr+2));
        vec4 = _mm256_mul_pd(carres, *(ptr+3));

        vec12 = _mm256_hadd_pd(vec1, vec2);
        vec34 = _mm256_hadd_pd(vec3, vec4);

        vecper1 = _mm256_permute4x64_pd(vec12, 0b11011000);
        vecper2 = _mm256_permute4x64_pd(vec34, 0b11011000);

        vectot = _mm256_hadd_pd(vecper1, vecper2);
        res = _mm256_sqrt_pd(vectot);

        total += sqrt(res[0] + res[1] + res[2] + res[3]);
    }
    
    return total;
}