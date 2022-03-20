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

#define c 1e-5
#define L 10
#define C 0.5
#define Iter 100000

double Tj(double prev, double current, double next) {
	
	double Tj = current + C * (prev - 2 * current + next);
	
	return Tj;
}

int main(int argc, char *argv[]){
	
	//Declaring variables
	double err, T_0, T_L, T_R, sum;
    int N, n = 0;
    double calcErr = 1e-25;

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

	// Vector Solucion
	double temperature[N], temperatureCopy[N];

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
    for (int i = 1; i < N - 1; i++) {
    	temperature[i] = T_0;
    }

	while (n < Iter && calcErr < err) {
    	
		// Calcular las temperaturas
    	for(int j = 1; j < N - 1; j++) {
			temperatureCopy[j] = Tj(temperature[j - 1], temperature[j], temperature[j + 1]);
		}

		// Update vector
        // Calc err
		sum = 0.0;
		for (int k = 1; k < N - 1; k++) {
			sum += temperatureCopy[k] - temperatureCopy[k - 1];
			temperature[k] = temperatureCopy[k];
		}
			
		calcErr = sum / N;
		n += 1;

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

	// Elapsed Time
    gettimeofday(&end, 0);
    
	long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    
	printf("\nElapsed Time: %.3f seg.\n", elapsed);

}