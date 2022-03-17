/*

        Proyecto #1
Programación Paralela con OpenMP

    Programa Secuencial

Creado por:

Juan Fernando De Leon Quezada       17822
Jose Amado Garcia                   18
Cristopher Barrios                  18

*/

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;


int main(){

    //Declaring variable
	int nx = 11;                        // Número de intervalos discretos
	double dt = 0.001;                  // intervalo de tiempo
	double dx = 0.1;                    // intervalo discreto de la distancia
	double r = dt / dx / dx;            // Constante de discretacion
	double error = 0;                   // Precisión o diferencia requerida


	vector<double> u(nx);               // Vector solución
	vector<double> u_old(nx);           // Vector solución

    // Inicializar el Vector U
	for (int i = 1; i <= nx - 1; ++i){
        if (i*dx >= 0.0 && i*dx <= 0.5){
			u[i] = 2 * i*dx;
		} else if (i*dx >= 0.5&&i*dx <= 1.0){
			u[i] = 2 * (1 - (i*dx));
		}
	}

    error = 0.001;
	while (error >= 0.0001)
	{
		// Copiando u a un arreglo temporal
		u_old = u;

		// Calculando nuevo u
		for (int i = 1; i <= nx - 2; i++)
		{
			u[i] = (r*u_old[i - 1]) + ((1 - (2 * r))*u_old[i]) + (r*u_old[i + 1]);
		}

		// Calculando error

		for (int i = 0; i <= nx - 1; i++)
		{
			double de = abs(u[i] - u_old[i]);	// Error Absoluto
			error = max(error, de);			// Error Maximum 
            // printf("U: %f \n", u[i]);
            // printf("U_OLD: %f \n", u_old[i]);
            // printf("Absolute Error: %f", de);
            // printf("Error: %f", error);
		}
		
        // break;
	}

}