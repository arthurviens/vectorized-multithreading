/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fichier main
 */
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "exo1.h"


int N = 1024 * 1024;

/*! 
 * \fn double now()
 * \author VIENS Arthur
 * \date 31/10/2021
 * \brief Exécute le programme
 * \version 0.1
 * \return Current Time
 */
double now(){
   struct timeval t; double f_t;
   gettimeofday(&t, NULL); 
   f_t = t.tv_usec; f_t = f_t/1000000.0; f_t +=t.tv_sec;
   return f_t; 
}

void unit_checks() {
	unit_check_norm4();
}

/*! 
 * \fn int main(int argc, char** argv)
 * \author VIENS Arthur
 * \date 31/10/2021
 * \brief Exécute le programme
 * \version 0.1
 * \param argc : nombre d'arguments
 * \param char** argv : tableau des arguments
 * \return 0
 */
int main(int argc, char** argv) {
	/* Declarations */
	unsigned int L;
	unsigned int i;
	double t0, t1, basic_t, a, b, c, d, res;
	double* U;

	/* Initialisations */
	a = 2.;
	b = 4.;
	c = 6.;
	d = 8.;
	L = 32;
	U = malloc(N * sizeof(double) + L);
	while (((long int)U % L) != 0) {
		U =(double*)((long int)U + 1);
	}

	for(i = 0; i < N; i++) {
		U[i] = i + 1.;
	}

	/* Body */
	unit_checks();

	t0 = now();
	res = norm4(U, a, b, c, d, N);
	t1 = now();
	basic_t = (t1 - t0) * 1000;
	printf("Res = %f. Temps d'exécution de norm4 version basique pour N = %i : %6.6fms \n", res, N, basic_t);


	return 0;
	}