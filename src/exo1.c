/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fonctions pour l'exercice 1
 */
#include <math.h>
#include "exo1.h"


double norm4(double *U, double a, double b, double c, double d, int n){
    /* Declarations */
    unsigned int i;
    double s;

    /* Initialisations */
    s = 0;

    /* Body */ 
    for(i = 0; i < (n / 4); i++) {
        s += sqrt(a*a*U[4*i] + b*b*U[4*i+1] + c*c*U[4*i+2] + d*d*U[4*i+3]);
    } 

    return s;
}

void unit_check_norm4() {
    /* Declarations */
    int n;
	double a, b, c, d, res;
	double* U;

    /* Initialisations */
	a = 1.;	b = 2.;	c = 3.;	d = 4.;
	n = 4;

    /* Body */
	U = malloc(n * sizeof(double));
	U[0] = 5.;
	U[1] = 4.5;
	U[2] = 4.;
	U[3] = 6.;

	res = norm4(U, a, b, c, d, n);
	
	/* Should be equal to */
	assert(res = 12.449900);
}