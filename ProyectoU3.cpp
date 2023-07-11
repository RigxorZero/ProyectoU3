#include <iostream>
#include <string>
#include <random>
#include <set>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;
using std::cout;
using std::endl;

// Imprimir algoritmo mas rapido
void masRapido(int algoritmoMasRapido, double tiempoMasRapido)
{
    cout << "El ganador es: ";

    switch (algoritmoMasRapido)
    {
    case 1:
        cout << "Bubble Sort";
        break;
    case 2:
        cout << "Heap Sort";
        break;
    case 3:
        cout << "Quick Sort";
        break;
    case 4:
        cout << "Merge Sort";
        break;
    case 5:
        cout << "Selection Sort";
        break;
    case 6:
        cout << "Insertion Sort";
        break;
    case 7:
        cout << "Shell Sort";
        break;
    default:
        break;
    }

    cout << " con un tiempo de " << tiempoMasRapido << " segundos" << endl;
}

// Bubble Sort
void bubbleSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int i = 0; i < tamano - 1; ++i)
    {
        for (int j = 0; j < tamano - i - 1; ++j)
        {
            if (orden)
            {
                if (datos[j] > datos[j + 1])
                {
                    swap(datos[j], datos[j + 1]);
                }
            }
            else
            {
                if (datos[j] < datos[j + 1])
                {
                    swap(datos[j], datos[j + 1]);
                }
            }
        }
    }
}

void heapify(vector<int>& datos, int tamano, int indice, bool orden)
{
    int mayor = indice;
    int izquierda = 2 * indice + 1;
    int derecha = 2 * indice + 2;

    if (orden)
    {
        if (izquierda < tamano && datos[izquierda] > datos[mayor])
        {
            mayor = izquierda;
        }

        if (derecha < tamano && datos[derecha] > datos[mayor])
        {
            mayor = derecha;
        }
    }
    else
    {
        if (izquierda < tamano && datos[izquierda] < datos[mayor])
        {
            mayor = izquierda;
        }

        if (derecha < tamano && datos[derecha] < datos[mayor])
        {
            mayor = derecha;
        }
    }

    if (mayor != indice)
    {
        swap(datos[indice], datos[mayor]);
        heapify(datos, tamano, mayor, orden);
    }
}

// Heap Sort
void heapSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int i = tamano / 2 - 1; i >= 0; --i)
    {
        heapify(datos, tamano, i, orden);
    }

    for (int i = tamano - 1; i >= 0; --i)
    {
        swap(datos[0], datos[i]);
        heapify(datos, i, 0, orden);
    }
}

int partition(vector<int>& datos, int inicio, int fin, bool orden)
{
    int pivote = datos[fin];
    int i = inicio - 1;

    for (int j = inicio; j <= fin - 1; ++j)
    {
        if (orden)
        {
            if (datos[j] < pivote)
            {
                ++i;
                swap(datos[i], datos[j]);
            }
        }
        else
        {
            if (datos[j] > pivote)
            {
                ++i;
                swap(datos[i], datos[j]);
            }
        }
    }

    swap(datos[i + 1], datos[fin]);
    return i + 1;
}

// Quick Sort
void quickSort(vector<int>& datos, int inicio, int fin, bool orden)
{
    if (inicio < fin)
    {
        int indicePivote = partition(datos, inicio, fin, orden);
        quickSort(datos, inicio, indicePivote - 1, orden);
        quickSort(datos, indicePivote + 1, fin, orden);
    }
}

void merge(vector<int>& datos, int inicio, int medio, int fin, bool orden)
{
    int tamanoIzquierda = medio - inicio + 1;
    int tamanoDerecha = fin - medio;

    vector<int> izquierda(datos.begin() + inicio, datos.begin() + medio + 1);
    vector<int> derecha(datos.begin() + medio + 1, datos.begin() + fin + 1);

    int indiceIzquierda = 0;
    int indiceDerecha = 0;
    int indiceMerge = inicio;

    while (indiceIzquierda < tamanoIzquierda && indiceDerecha < tamanoDerecha)
    {
        if (orden)
        {
            if (izquierda[indiceIzquierda] <= derecha[indiceDerecha])
            {
                datos[indiceMerge] = izquierda[indiceIzquierda];
                ++indiceIzquierda;
            }
            else
            {
                datos[indiceMerge] = derecha[indiceDerecha];
                ++indiceDerecha;
            }
        }
        else
        {
            if (izquierda[indiceIzquierda] >= derecha[indiceDerecha])
            {
                datos[indiceMerge] = izquierda[indiceIzquierda];
                ++indiceIzquierda;
            }
            else
            {
                datos[indiceMerge] = derecha[indiceDerecha];
                ++indiceDerecha;
            }
        }
        ++indiceMerge;
    }

    while (indiceIzquierda < tamanoIzquierda)
    {
        datos[indiceMerge] = izquierda[indiceIzquierda];
        ++indiceIzquierda;
        ++indiceMerge;
    }

    while (indiceDerecha < tamanoDerecha)
    {
        datos[indiceMerge] = derecha[indiceDerecha];
        ++indiceDerecha;
        ++indiceMerge;
    }
}

// Merge Sort
void mergeSort(vector<int>& datos, int inicio, int fin, bool orden)
{
    if (inicio < fin)
    {
        int medio = inicio + (fin - inicio) / 2;
        mergeSort(datos, inicio, medio, orden);
        mergeSort(datos, medio + 1, fin, orden);
        merge(datos, inicio, medio, fin, orden);
    }
}

// Selection Sort
void selectionSort(vector<int>& datos, bool ascendente)
{
    int tamano = datos.size();

    for (int i = 0; i < tamano - 1; ++i)
    {
        int indiceExtremo = i;
        for (int j = i + 1; j < tamano; ++j)
        {
            if (ascendente)
            {
                if (datos[j] < datos[indiceExtremo])
                {
                    indiceExtremo = j;
                }
            }
            else
            {
                if (datos[j] > datos[indiceExtremo])
                {
                    indiceExtremo = j;
                }
            }
        }
        swap(datos[i], datos[indiceExtremo]);
    }
}

// Insertion Sort
void insertionSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int i = 1; i < tamano; ++i)
    {
        int valorActual = datos[i];
        int j = i - 1;
        if (orden)
        {
            while (j >= 0 && datos[j] > valorActual)
            {
                datos[j + 1] = datos[j];
                --j;
            }
        }
        else
        {
            while (j >= 0 && datos[j] < valorActual)
            {
                datos[j + 1] = datos[j];
                --j;
            }
        }
        datos[j + 1] = valorActual;
    }
}

// Shell Sort
void shellSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();
    for (int brecha = tamano / 2; brecha > 0; brecha /= 2)
    {
        for (int i = brecha; i < tamano; ++i)
        {
            int valorActual = datos[i];
            int j = i;
            if (orden)
            {
                while (j >= brecha && datos[j - brecha] > valorActual)
                {
                    datos[j] = datos[j - brecha];
                    j -= brecha;
                }
            }
            else
            {
                while (j >= brecha && datos[j - brecha] < valorActual)
                {
                    datos[j] = datos[j - brecha];
                    j -= brecha;
                }
            }
            datos[j] = valorActual;
        }
    }
}


// Función para realizar la carrera
void carrera(int set, vector<int>& datos, bool orden) 
{
    switch (set)
    {
    case 1:
        cout << " Modo Aleatorio sin repetir" << endl;
        break;
    case 2:
        cout << " Modo Aleatorio con repetir" << endl;
        break;
    case 3:
        cout << " Modo Ordenado" << endl;
        break;
    case 4:
        cout << " Modo Inversamente Ordenado" << endl;
        break;
    default:
        break;
    }

    // Variables para el algoritmo más rápido
    int algoritmoMasRapido = -1;
    double tiempoMasRapido = std::numeric_limits<double>::max();

    // BubbleSort
    vector<int> a1 = datos;
    auto inicio = std::chrono::high_resolution_clock::now();
    bubbleSort(a1, orden);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    cout << "1. Bubble Sort, " << duracion.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 1;
        tiempoMasRapido = duracion.count();
    }

    // HeapSort
    vector<int> a2 = datos;
    inicio = std::chrono::high_resolution_clock::now();
    heapSort(a2, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion2 = fin - inicio;
    cout << "2. Heap Sort, " << duracion2.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion2.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 2;
        tiempoMasRapido = duracion2.count();
    }

    // Quick Sort
    vector<int> a3 = datos;
     inicio = std::chrono::high_resolution_clock::now();
    quickSort(a3, 0, a3.size() - 1, true);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion3 = fin - inicio;
    cout << "3. Quick Sort, " << duracion3.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion3.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 3;
        tiempoMasRapido = duracion3.count();
    }

    // Merge Sort
    vector<int> a4 = datos;
    inicio = std::chrono::high_resolution_clock::now();
    mergeSort(a4, 0, a4.size() - 1, true);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion4 = fin - inicio;
    cout << "4. Merge Sort, " << duracion4.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion4.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 4;
        tiempoMasRapido = duracion4.count();
    }

    // Selection Sort
    vector<int> a5 = datos;
    inicio = std::chrono::high_resolution_clock::now();
    selectionSort(a5, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion5 = fin - inicio;
    cout << "5. Selection Sort, " << duracion5.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion5.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 5;
        tiempoMasRapido = duracion5.count();
    }

    // Insertion Sort
    vector<int> a6 = datos;
    inicio = std::chrono::high_resolution_clock::now();
    insertionSort(a6, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion6 = fin - inicio;
    cout << "6. Insertion Sort, " << duracion6.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion6.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 6;
        tiempoMasRapido = duracion6.count();
    }

    // Shell Sort
    vector<int> a7 = datos;
    inicio = std::chrono::high_resolution_clock::now();
    shellSort(a7, orden);
    fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion7 = fin - inicio;
    cout << "7. Shell Sort, " << duracion7.count() << " segundos" << endl;

    // Actualizar el algoritmo más rápido
    if (duracion7.count() < tiempoMasRapido)
    {
        algoritmoMasRapido = 7;
        tiempoMasRapido = duracion7.count();
    }
    
    masRapido(algoritmoMasRapido, tiempoMasRapido);

}

int main() 
{
    /* TABLERO DE PUNTAJES */
    // Configuración de la generación de números aleatorios
    random_device rd;
    mt19937 gen(rd());

    // Cantidad de números aleatorios a generar (entre 90.000 y 100.000)
    uniform_int_distribution<int> dis_count(90000, 100000);
    int num_count = dis_count(gen);

    // Generar números aleatorios únicos
    set<int> random_numbers_score;
    while (random_numbers_score.size() < num_count)
    {
        uniform_int_distribution<int> dis_range(0, 1000000);
        int num = dis_range(gen);
        random_numbers_score.insert(num);
    }

    // Convertir el set en un vector y desordenar los números
    vector<int> random_vector_score(random_numbers_score.begin(), random_numbers_score.end());
    shuffle(random_vector_score.begin(), random_vector_score.end(), gen);

    // Generar números aleatorios para el conjunto Aleatorio con duplicados (sin negativos)
    vector<int> random_duplicates_score(num_count);
    uniform_int_distribution<int> dis_positive(0, numeric_limits<int>::max());
    generate(random_duplicates_score.begin(), random_duplicates_score.end(), [&gen, &dis_positive]() { return dis_positive(gen); });

    // Generar números ordenados para el conjunto Ordenado (ascendente)
    vector<int> ordered_vector_score(num_count);
    iota(ordered_vector_score.begin(), ordered_vector_score.end(), 1);

    // Generar números ordenados en forma inversa para el conjunto Inversamente ordenado (descendente)
    vector<int> reverse_ordered_vector_score(num_count);
    iota(reverse_ordered_vector_score.rbegin(), reverse_ordered_vector_score.rend(), 1);

    // Desordenar los conjuntos de datos adicionales
    shuffle(random_duplicates_score.begin(), random_duplicates_score.end(), gen);
    //shuffle(ordered_vector_score.begin(), ordered_vector_score.end(), gen);
    //shuffle(reverse_ordered_vector_score.begin(), reverse_ordered_vector_score.end(), gen);

    /* CAMINOS ENTRE ALDEAS */
    // Cantidad de números aleatorios a generar (entre 50.000 y 70.000)
    uniform_int_distribution<int> dis_count_roads(50000, 70000);
    int num_count_roads = dis_count_roads(gen);

    // Generar números aleatorios únicos
    set<int> random_numbers_roads;
    while (random_numbers_roads.size() < num_count_roads)
    {
        uniform_int_distribution<int> dis_range(0, 1000000);
        int num = dis_range(gen);
        random_numbers_roads.insert(num);
    }

    // Convertir el set en un vector y desordenar los números
    vector<int> random_vector_roads(random_numbers_roads.begin(), random_numbers_roads.end());
    shuffle(random_vector_roads.begin(), random_vector_roads.end(), gen);

    // Generar números aleatorios para el conjunto Aleatorio con duplicados (sin negativos)
    vector<int> random_duplicates_roads(num_count);
    uniform_int_distribution<int> dis_positive_roads(0, numeric_limits<int>::max());
    generate(random_duplicates_roads.begin(), random_duplicates_roads.end(), [&gen, &dis_positive_roads]() { return dis_positive_roads(gen); });

    // Generar números ordenados para el conjunto Ordenado (ascendente)
    vector<int> ordered_vector_roads(num_count);
    iota(ordered_vector_roads.begin(), ordered_vector_roads.end(), 1);

    // Generar números ordenados en forma inversa para el conjunto Inversamente ordenado (descendente)
    vector<int> reverse_ordered_vector_roads(num_count);
    iota(reverse_ordered_vector_roads.rbegin(), reverse_ordered_vector_roads.rend(), 1);

    // Desordenar los conjuntos de datos adicionales
    shuffle(random_duplicates_roads.begin(), random_duplicates_roads.end(), gen);
    shuffle(ordered_vector_roads.begin(), ordered_vector_roads.end(), gen);
    shuffle(reverse_ordered_vector_roads.begin(), reverse_ordered_vector_roads.end(), gen);

    cout << "Datos en arreglo 1 " << random_numbers_score.size() << endl;
    cout << "Datos en arreglo 2 " << random_numbers_roads.size() << endl;

    cout << "Carrera de algoritmos" << endl;
    cout << "1. Ascendente." << endl; // true
    cout << "2. Decendiente" << endl; // false
    cout << "Opción elegida: " << endl;
    int opcion;
    cin >> opcion;

    // Seleccionar el algoritmo de ordenamiento según la opción ingresada
    switch (opcion) 
    {
        case 1:
            
            // Ejecutar el algoritmo de ordenamiento ascendente con los datos generados para el tablero
            cout << "Carrera con el Tablero:";
            carrera(1, random_vector_score, true);
            carrera(2, random_duplicates_score, true);
            carrera(3, ordered_vector_score, true);
            carrera(4, reverse_ordered_vector_score, true);
            // Ejecutar el algoritmo de ordenamiento ascendente con los datos generados para los caminos
            cout << "Carrera con los posibles Caminos:";
            carrera(1, random_vector_roads, true);
            carrera(2, random_duplicates_roads, true);
            carrera(3, ordered_vector_roads, true);
            carrera(4, reverse_ordered_vector_roads, true);
            break;
        case 2:
            // Ejecutar el algoritmo de ordenamiento descendente con los datos generados para el tablero
            cout << "Carrera con el Tablero:";
            carrera(1, random_vector_score, false);
            carrera(2, random_duplicates_score, false);
            carrera(3, ordered_vector_score, false);
            carrera(4, reverse_ordered_vector_score, false);
            // Ejecutar el algoritmo de ordenamiento ascendente con los datos generados para los caminos
            cout << "Carrera con los posibles Caminos:";
            carrera(1, random_vector_roads, false);
            carrera(2, random_duplicates_roads, false);
            carrera(3, ordered_vector_roads, false);
            carrera(4, reverse_ordered_vector_roads, false);
            break;
        default:
            std::cout << "Opción inválida" << std::endl;
            break;
    }
    return 0;
}