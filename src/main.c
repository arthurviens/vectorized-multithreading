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

int N = 1024 * 1024;

/*! 
 * \fn double now()
 * \brief Renvoie le temps actuel de l'horloge
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

double mean(double* a, int n) {
	int i;
	double sum;
	sum = 0;
	for (i = 0; i < n; i++) {
		sum += a[i];
	}
	return (sum / n);	
}

double std(double* a, int n){
	int i;
	double var, local_mean;
	local_mean = mean(a, n);
	var = 0;
	for (i = 0; i < n; i++) {
		var += (a[i] - local_mean) * (a[i] - local_mean);
	}
	return sqrt(var / n);	
}

double* timeOf100Calls(double (*f)(double*, double, double, double, double, int), 
						double* U, double a, double b, double c, double d, int N) {
	
	double t0, t1, res, mean_times, mean_val, std_times, std_val;
	int i;
	double* mean_std = malloc(2 * sizeof(double));
	double* times = malloc(100 * sizeof(double));
	double* values = malloc(100 * sizeof(double));
	
	for (i = 0; i < 100; ++i) {
		t0 = now();
		res = f(U, a, b, c, d, N);
		t1 = now();
		times[i] = t1 - t0; 
		values[i] = res;
	}

	mean_times = mean(times, 100);
	mean_val = mean(values, 100);

	assert(mean_val = 1315061951.047256); /* check result */

	std_times = std(times, 100);
	std_val = std(values, 100);

	assert(std_val < 0.001); /* check result */

	mean_std[0] = mean_times;
	mean_std[1] = std_times;

	printf("Résultat : %f\n", mean_val);
	return mean_std;
}

/*! 
 * \fn int main(int argc, char** argv)
 * \brief Exécute le programme
 * \param argc : nombre d'arguments
 * \param char** argv : tableau des arguments
 * \return 0
 */
int main(int argc, char** argv) {
	/* Declarations */
	unsigned int L;
	unsigned int i;
	double a, b, c, d;
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
	unit_checks();

	mean_std = timeOf100Calls(norm4, U, a, b, c, d, N);
	printf("Resultat correct. Temps d'exécution de norm4 (séquentiel) pour N = %i \n", N);
	printf(" --> Temps moyen pour 100 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	
	mean_std = timeOf100Calls(vect_norm4, U, a, b, c, d, N);
	printf("Resultat correct. Temps d'exécution de vect_norm4 (vectoriel) pour N = %i \n", N);
	printf(" --> Temps moyen pour 100 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	
	test_permute();

	return 0;
	}