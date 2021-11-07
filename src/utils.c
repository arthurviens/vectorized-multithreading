#include "math.h"
#include <time.h>
#include <sys/time.h>
#include "utils.h"
#include "exo1.h"

int K = 1000;

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

void unit_checks(double *U) {
	assert(U);
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

double* timeOfKCalls(double (*f)(double*, double, double, double, double, int), 
						double* U, double a, double b, double c, double d, int N) {
	
	double t0, t1, res, mean_times, mean_val, std_times, std_val;
	int i;
	double* mean_std = malloc(2 * sizeof(double));
	double* times = malloc(K * sizeof(double));
	double* values = malloc(K * sizeof(double));
	
	for (i = 0; i < K; ++i) {
		t0 = now();
		res = f(U, a, b, c, d, N);
		t1 = now();
		times[i] = t1 - t0; 
		values[i] = res;
	}

	mean_times = mean(times, K);
	mean_val = mean(values, K);

	std_times = std(times, K);
	std_val = std(values, K);

	assert(std_val < 0.001); /* check result */

	mean_std[0] = mean_times;
	mean_std[1] = std_times;

	printf("# Résultat : %f\n", mean_val);
	return mean_std;
}

double* timeOfKCallsThread(double (*f)(double*, double, double, double, double, int, int, int), 
						double* U, double a, double b, double c, double d, int N, int nb_threads, int mode) {
	
	double t0, t1, res, mean_times, mean_val, std_times, std_val;
	int i;
	double* mean_std = malloc(2 * sizeof(double));
	double* times = malloc(K * sizeof(double));
	double* values = malloc(K * sizeof(double));
	
	for (i = 0; i < K; ++i) {
		t0 = now();
		res = f(U, a, b, c, d, N, nb_threads, mode);
		t1 = now();
		times[i] = t1 - t0; 
		values[i] = res;
	}

	mean_times = mean(times, K);
	mean_val = mean(values, K);

	std_times = std(times, K);
	std_val = std(values, K);

	assert(std_val < 0.001); /* check result */

	mean_std[0] = mean_times;
	mean_std[1] = std_times;

	printf("# Résultat : %f\n", mean_val);
	return mean_std;
}