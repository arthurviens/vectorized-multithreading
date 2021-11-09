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

/* VERSION SCALAIRE OPTIMISEE - ETALON pour l'accélération */ 
/*! 
 * \fn double norm4(double *U, double a, double b, double c, double d, int n)
 * \brief standard calculation
 * \param double* U : Data
 * \param double a : parameter of the formula
 * \param double b : parameter of the formula
 * \param double c : parameter of the formula
 * \param double d : parameter of the formula
 * \param int n : size of the data
 * \return result
 */
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

/*! 
 * \fn void unit_check_norm4()
 * \brief exercise 1 unit checks
 * \return nothing
 */
void unit_check_norm4() {
    /* Declarations */
    int n, i;
	double a, b, c, d, res;
	double* U;

    /* Initialisations */
	a = 1.;	b = 2.;	c = 3.;	d = 4.;
	n = 16; 

    /* Body */
	U = malloc(n * sizeof(double));
    for (i = 0; i < n; i++) {
	    U[i] = i;
    }

	res = norm4(U, a, b, c, d, n);
    
	/* Should be equal to */
	assert(abs(res -  60.493907) < 0.00001);
}