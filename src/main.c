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
#include <math.h>

#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "utils.h"

int N = 1024 * 1024;


/*! 
 * \fn int main(int argc, char** argv)
 * \brief Exécute le programme
 * \param argc : nombre d'arguments
 * \param char** argv : tableau des arguments
 * \return 0
 */
int main(int argc, char** argv) {
	/* Declarations */
	unsigned int L, i, nb_threads;
	double a, b, c, d, t_seq, t_vect, res, t0, t1;
	double* U, *mean_std;

	/* Initialisations */
	a = 2.;
	b = 3.;
	c = 4.;
	d = 5.;
	L = 32;
	U = malloc(N * sizeof(double) + L);
	while (((long int)U % L) != 0) {
		U =(double*)((long int)U + 1);
	}

	for(i = 0; i < N; i++) {
		U[i] = i + 1.;
	}

	/* Body */
	unit_checks(U);

	mean_std = timeOf100Calls(norm4, U, a, b, c, d, N);
	printf("Resultat correct. Temps d'exécution de norm4 (séquentiel) pour N = %i \n", N);
	printf(" --> Temps moyen pour 100 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	t_seq = mean_std[0];
	
	mean_std = timeOf100Calls(vect_norm4, U, a, b, c, d, N);
	printf("Resultat correct. Temps d'exécution de vect_norm4 (vectoriel) pour N = %i \n", N);
	printf(" --> Temps moyen pour 100 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	t_vect = mean_std[0];

	printf("    -----    \n");
	printf("Cela représente une acceleration de %f\n", t_seq / t_vect);

	nb_threads = 4;
	t0 = now();
	res = norm4Par(U, a, b, c, d, N, nb_threads);
	t1 = now();
	printf("Resultat : %f\n", res);
	printf("Temps d'execution en threadé : %fms\n", (t1 - t0) * 1000);

	return 0;
}