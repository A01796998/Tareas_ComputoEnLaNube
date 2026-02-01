#include <iostream>

#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif

#define N 24 // Más que una variable, esta es una directiva que antes de compiilar, donde vea una N la sustituira con 24
using namespace std; // Le indica al compilador que estamos cargando el estandar std, de esto modo ya no tenemos que escribir std::cout por ejemplo
int tid; // Definimos una variable global

int main(){

	double start = omp_get_wtime();

	cout << "Estableciendo la cantidad de Hilos!\n" << endl;
	int nHilos;
	cout << "Cuantos hilos quieres trabajar: " << endl ;
	cin >> nHilos; // Le pedimos como output en la consola que ingrese cantidad de operaciones

	#ifdef _OPENMP
		omp_set_num_threads(nHilos); // Por defecto si no indicamos la cantidad de hilos, tomará tantos como el procesador lógico, por ejemplo en mi caso 16, pero con esta opcion, si pedimos de menos, dejaremos hilos sin hacer nada, pero si le pedimos de más, cada hilo aplicará concurrencia para gestionar sus hilos asignados, si le pido que sean por ejemplo 32, mis 16 hilos cada uno aplicaría concurrencia para gestionar 2 hilos 
	#endif

	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		cout << "El thread " << tid << " esta en marcha " << endl;
		cout << "El thread " << tid << " ha terminado " << endl;
	}

	double end = omp_get_wtime();

	cout << "Tiempo transcurrido: " << end - start << endl;// Muestra el tiempo que duró la ejecución del programa3
}
