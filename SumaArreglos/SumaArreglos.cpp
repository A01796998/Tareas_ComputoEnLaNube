#include <iostream> // Libreria para permitir la entrada y salida de datos desde la consola

#ifdef _OPENMP // Revisa si el proyecto permite las directivas de OpenMP
    #include <omp.h> // Si tiene permitido el uso de OpenMP incluye su libreria
#else
    #define omp_get_thread_num() 0 // Si no tiene permitido, define el uso nulo de hilos
#endif

#define N 1000 // Más que una variable, esta es una directiva que antes de compiilar, donde vea una "N" la sustituira con 1000
#define chunk 100 // Más que una variable, esta es una directiva que antes de compiilar, donde vea un "chunk" la sustituira con 100
#define mostrar 10 // Más que una variable, esta es una directiva que antes de compiilar, donde vea un "mostrar" la sustituira con 10
using namespace std; // Le indica al compilador que estamos cargando el estandar std, de esto modo ya no tenemos que escribir "std::cout" por ejemplo, solo "cout"

void imprimeArreglo(float *d); // Notificamos al compilador de que estaremos haciendo uso de una función que no regresa ningún elemento (tomando como objeto un puntero)

int main(){
    cout << "--Sumando arreglos en paralelo--\n" << endl; // Impresion de texto (Escribimos algo y lo mandamos a consola)

    float a[N], b[N], c[N]; // Declaramos arreglos
    int i, mult, sum; // Declaramos variables
    int pedazos = chunk; // Inicializamos variable con nuestra directiva

    cout << "Que numero multiplicara el primer arreglo: " << endl; // Impresion de texto (Escribimos algo y lo mandamos a consola)
    cin >> mult; // Entrada de texto

    cout << "Que numero sumara el primer arreglo: " << endl; // Impresion de texto (Escribimos algo y lo mandamos a consola)
    cin >> sum; // Entrada de texto

    for (i = 0; i < N; i++) { // Ciclo "for" iniciado en 0, incrementando +1 en cada ciclo y que correrá 1000 ciclos (Acotado con la directiva "N")
        a[i] = i * mult; // Multiplicamos cada posición 
        b[i] = (i + sum); // Sumamos en cada posición
    }
    
    #ifdef _OPENMP
        omp_set_num_threads(10); // Indicamos cuantos hilos usaremos 
    #endif

    // Iniciamos región paralela:
    // 1. Le dice a los hilos que los arreglos y la variable "pedazos" son comunes
    // 2. Con esto hacemos que el contador de nuestro ciclo "for" sea privado y asi cada hilo tenga su propio contador y no sobreescriban lo de los demas
    // 3. Se reparten por bloques la información completa antes de que empiece el bucle, para que cada  hilo tenga que hacer 100 sumas 
    #pragma omp parallel for \
    shared(a,b,c,pedazos) \
    private(i) \
    schedule(static, pedazos)
    
    for (i = 0; i < N; i++) // Ciclo "for" iniciado en 0, incrementando +1 en cada ciclo y que correrá 1000 ciclos (Acotado con la directiva "N")
        c[i] = a[i] + b[i]; // Hacemos la suma para cada posición

    cout << "Imprimiendo primeras entradas del arreglo 'a'" << endl; // Impresion de texto (Escribimos algo y lo mandamos a consola)
    imprimeArreglo(a); // Hacmos llamado a nuestra funcion de impresion
    cout << "Imprimiendo primeras entradas del arreglo 'b'" << endl; // Impresion de texto (Escribimos algo y lo mandamos a consola)
    imprimeArreglo(b); // Hacmos llamado a nuestra funcion de impresion
    cout << "Imprimiendo primeras entradas del arreglo 'c'" << endl; // Impresion de texto (Escribimos algo y lo mandamos a consola)
    imprimeArreglo(c); // Hacmos llamado a nuestra funcion de impresion

}

void imprimeArreglo(float *d) { // Recibe el puntero (espacio en nuestra memoria del arreglo que queremos imprimir
    for (int x = 0; x < mostrar; x++) { // Ciclo "for" iniciado en 0, incrementando +1 en cada ciclo y que correrá 10 ciclos (Acotado con la directiva "mostrar")
        cout << d[x] << " - "; // Se coloca en el buffer de la consola la posición "x" de nuestro arreglo
    }
    cout << endl;// Se imprime todo lo que teniamos en nuestro buffer para imprimir
}