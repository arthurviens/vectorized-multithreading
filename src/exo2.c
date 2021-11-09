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

void print_m256d(__m256d vec) {
    printf("Vec(%f,%f,%f,%f)\n", vec[0], vec[1], vec[2], vec[3]);
}

/*! 
 * \fn double vect_norm4(double *U, double a, double b, double c, double d, int n)
 * \brief vectorized calculation
 * \param double* U : Data
 * \param double a : parameter of the formula
 * \param double b : parameter of the formula
 * \param double c : parameter of the formula
 * \param double d : parameter of the formula
 * \param int n : size of the data
 * \return result
 */
double vect_norm4(double *U, double a, double b, double c, double d, int n) {
    /* Declarations */
    int i;
    
    __m256d *ptr = (__m256d*)U;
    __m256d carres = _mm256_set_pd(a*a, b*b, c*c, d*d);
    __m256d res = _mm256_set_pd(0,0,0,0);
    __m256d tmp = _mm256_set_pd(0,0,0,0);

    /* Initialisations */

/*    for(i = 0; i < n/4; i++) {
		assert((*(ptr+i))[0] == 1);
		assert((*(ptr+i+1))[1] == 1);
	}*/
    /* Body */ 

    /* Version condensée pour éviter d'avoir des accès mémoire intermédiaires */
    /* Voir version ci-après équivalente pour explications */
    
    for(i = 0; i < (n/4); i += 4, ptr += 4) {
        tmp += _mm256_sqrt_pd(_mm256_hadd_pd(_mm256_permute4x64_pd(_mm256_hadd_pd(_mm256_mul_pd(carres, *ptr), _mm256_mul_pd(carres, *(ptr+1))), 0b11011000),
            _mm256_permute4x64_pd(_mm256_hadd_pd(_mm256_mul_pd(carres, *(ptr+2)), _mm256_mul_pd(carres, *(ptr+3))), 0b11011000)));
        printf("i = %d, sum(res) = %f, res = ", i, tmp[0]+tmp[1]+tmp[2]+tmp[3]);
        printf("Résultat des quatre : ");
        print_m256d((*ptr));
        print_m256d(*(ptr+1));
        print_m256d(*(ptr+2));
        print_m256d(*(ptr+3));
        printf("Ce qui donne : ");
        print_m256d(tmp);
        fflush(stdout);
        res += tmp;
    }

    return (res[0] + res[1] + res[2] + res[3]);
}


/* Version équivalente, avec valeurs intermédiaires --> Explications
for(i = 0; i < (n/4); i += 4, ptr += 4) {
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

/*! 
 * \fn void unit_check_norm4()
 * \brief exercise 2 unit checks
 * \return nothing
 */
void unit_check_vect_norm4() {
    /* Declarations */
    int n, i, L;
	double a, b, c, d, res;
	double* U;

    /* Initialisations */
	a = 1.;	b = 2.;	c = 3.;	d = 4.;
	n = 16; 
    L = 32;

    /* Body */
	U = malloc(n * sizeof(double) + L);
	while (((long int)U % L) != 0) {
		U =(double*)((long int)U + 1);
	}
    for (i = 0; i < n; i++) {
	    U[i] = 1;
    }

	res = vect_norm4(U, a, b, c, d, n);
	/* Should be equal to */
	assert(abs(res -  21.908902) < 0.00001);
}