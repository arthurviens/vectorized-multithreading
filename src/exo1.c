/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fonctions pour l'exercice 1
 */
#include <stdio.h>
#include <math.h>
#include "exo1.h"


double norm4(double *U, double a, double b, double c, double d, int n){
    /* Declarations */
    unsigned int i;
    double s;
    double aa;
    double bb;
    double cc;
    double dd;

    /* Initialisations */
    s = 0;
    aa = a*a;
    bb = b*b;
    cc = c*c;
    dd = d*d;

    /* Body */ 
    for(i = 0; i < n; i+=4) {
        s += sqrt(aa * U[i] + bb * U[i+1] + cc * U[i+2] + dd * U[i+3]);
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
    fflush(stdout);
	assert(abs(res - 12.449900) < 0.00001);
}