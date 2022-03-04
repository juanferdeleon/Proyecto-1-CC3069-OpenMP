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

}