/*

        Proyecto #1
Programación Paralela con OpenMP

    Programa Secuencial

Creado por:

Juan Fernando De Leon Quezada       17822
Jose Amado Garcia                   18
Cristopher Barrios                  18

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

#define c 1e-5
#define L 10
#define C 0.5
#define Iter 100000

int thread_count;

double Tj(double prev, double curr, double next) {
	return curr + C * (prev - 2 * curr + next);
}

double heatDisipationParallel(double *data, double *dataCopy, int N, int id, int count, int chunkSize) {
	
    int start, end;

    if (id != 1){
        start = (id - 1) * chunkSize;
    } else {
        start = 1;
    }

    if (id != count){
        end = id * chunkSize;
    } else {
        end = N - 1;
    }
	
	// Temp calc
	for(int j = start; j < end; ++j) {
		dataCopy[j] = Tj(data[j - 1], data[j], data[j + 1]);
	}
	
    // Update vector
    // Calc err
	double sum = 0.0;
	for (int k = 1; k < N - 1; ++k) {
		sum += dataCopy[k] - dataCopy[k - 1];
		data[k] = dataCopy[k];
	}
		
	return sum / N;
}


int main(int argc, char *argv[]) {
	
    thread_count = strtol(argv[1], NULL, 10);
    
    double err, T_0, T_L, T_R, calcErr = 1e-25;
    int N, i, t, chunkSize, n = 0;
    double *temperature, *temperatureCopy;

    printf("\n\n\tProyecto 1\n");
    printf("\n\nPrecision o diferencia requerida: ");
    scanf("%lf", &err);
    printf("Numero de intervalos discretos: ");
    scanf("%d", &N);
    printf("Temperatura inicial de toda la barra: ");
    scanf("%lf", &T_0);
    printf("Temperatura en la frontera izquierda (x=0): ");
    scanf("%lf", &T_L);
    printf("Temperatura en la frontera derecha (x=L): ");
    scanf("%lf", &T_R);
    
    // Malloc for temperature vector
    if ( (temperature = (double *)malloc(N * sizeof(double))) == NULL )
    perror("memory allocation for temperature");

	// Malloc for temperature copy vector
    if ( (temperatureCopy = (double *)malloc(N * sizeof(double))) == NULL )
    perror("memory allocation for temperatureCopy");
    
    // Medicion de tiempo
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    // Asignar las condiciones iniciales
    temperature[0] = T_L;
    temperature[N - 1] = T_R;
    // Asignar las condiciones iniciales
    temperatureCopy[0] = T_L;
    temperatureCopy[N - 1] = T_R;
    
    // Inicializar vector
    #pragma omp parallel for private(i)\
    schedule(guided, 8)
    for (i = 1; i < N - 1; ++i) {
    	temperature[i] = T_0;
    }
    
    chunkSize = (int) (N / thread_count * 1.0);
    
    #pragma omp parallel
    #pragma omp single nowait
    while (n < Iter && calcErr < err) {
    	for (t = 1; t <= thread_count; ++t) {
			#pragma omp task
			calcErr = heatDisipationParallel(temperature, temperatureCopy, N, t, thread_count, chunkSize);
		}
		
		++n;
	}

    int ctr = 0;

	// Mostrar resultados
    for (int i = 0; i < N; i++) {
        if (ctr%4 == 0) {
            printf("%lf \n", temperature[i]);
        } else {
            printf("%lf \t", temperature[i]);
        }
        ctr += 1;
	}

    free(temperature);
    free(temperatureCopy);
    
    // Elapsed Time
    gettimeofday(&end, 0);
    
	long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    
	printf("\nElapsed Time: %.3f seg.\n", elapsed);
}