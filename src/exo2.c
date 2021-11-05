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

    __m256d carres;
    __m256d *ptr;
    __m256d res;

    /* Initialisations */

    carres[0] = a*a; carres[1] = b*b; carres[2] = c*c; carres[3] = d*d;
    res[0] = 0; res[1] = 0; res[2] = 0; res[3] = 0; 

    ptr = (__m256d*)U;
    
    /* Body */ 

    /* Version condensée pour éviter d'avoir des accès mémoire intermédiaires */
    /* Voir version ci-après équivalente pour explications */
    for(i = 0; i < (n/4); i += 4, ptr += 4, U += 16) {
        res += _mm256_sqrt_pd(_mm256_hadd_pd(_mm256_permute4x64_pd(_mm256_hadd_pd(_mm256_mul_pd(carres, *ptr), _mm256_mul_pd(carres, *(ptr+1))), 0b11011000),
            _mm256_permute4x64_pd(_mm256_hadd_pd(_mm256_mul_pd(carres, *(ptr+2)), _mm256_mul_pd(carres, *(ptr+3))), 0b11011000)));
    }

    return (res[0] + res[1] + res[2] + res[3]);
}


/* Version équivalente, avec valeurs intermédiaires --> Explications
for(i = 0; i < (n/4); i += 4, ptr += 4, U += 16) {
    vec1 = _mm256_mul_pd(carres, *ptr);                 // On prend 4 vecteurs [a1, b1, c1, d1]
    vec2 = _mm256_mul_pd(carres, *(ptr+1));             // [a2, b2, c2, d2]
    vec3 = _mm256_mul_pd(carres, *(ptr+2));             // etc
    vec4 = _mm256_mul_pd(carres, *(ptr+3));

    vec12 = _mm256_hadd_pd(vec1, vec2);                 // On les additionne horizontalement [a1+b1, a2+b2, c1+d1, c2+d2]
    vec34 = _mm256_hadd_pd(vec3, vec4);                 // [a3+b3, a4+b4, c3+b3, c4+b4]
                                                        // On voudrait additionner a1+b1+c1+d1 sauf qu'ils sont pas au bon endroit
    vecper1 = _mm256_permute4x64_pd(vec12, 0b11011000); // On permute [a1+b1, c1+d1, a2+b2, c2+d2] --> on peut hadd
    vecper2 = _mm256_permute4x64_pd(vec34, 0b11011000); // vecteur binaire 00 10 01 11 --> premier inchangé, milieu permuté, dernier inchangé

    vectot = _mm256_hadd_pd(vecper1, vecper2);          // On additionne horizontalement [a1+b1+c1+d1, a2+b2+ ...etc]
    res = _mm256_sqrt_pd(vectot);                       // On peut donc vectoriser la racine carrée

    total += sqrt(res[0] + res[1] + res[2] + res[3]);   // On ajoute le résultat
} 
*/

    