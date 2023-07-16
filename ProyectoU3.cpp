#include <iostream>
#include <string>
#include <random>
#include <set>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <stack>
#include <utility>
#include <vector>
#include <numeric>

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

void quickSort(vector<int>& datos, int inicio, int fin, bool orden)
{
    stack<pair<int, int>> pila;
    pila.push(make_pair(inicio, fin));

    while (!pila.empty())
    {
        int inicioActual = pila.top().first;
        int finActual = pila.top().second;
        pila.pop();

        if (inicioActual >= finActual)
            continue;

        int pivote = datos[finActual];
        int i = inicioActual - 1;

        for (int j = inicioActual; j <= finActual - 1; ++j)
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

        swap(datos[i + 1], datos[finActual]);
        int indicePivote = i + 1;

        pila.push(make_pair(inicioActual, indicePivote - 1));
        pila.push(make_pair(indicePivote + 1, finActual));
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
void selectionSort(vector<int>& datos, bool orden)
{
    int tamano = datos.size();

    for (int i = 0; i < tamano - 1; ++i)
    {
        int indiceExtremo = i;
        for (int j = i + 1; j < tamano; ++j)
        {
            if (orden)
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
    quickSort(a3, 0, a3.size() - 1, orden);
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
    mergeSort(a4, 0, a4.size() - 1, orden);
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

// Función para generar números aleatorios únicos en un rango determinado
set<int> generateRandomNumbers(int count, int rangeStart, int rangeEnd)
{
    random_device rd;
    mt19937 gen(rd());
    set<int> randomNumbers;

    while (randomNumbers.size() < count)
    {
        uniform_int_distribution<int> dis_range(rangeStart, rangeEnd);
        int num = dis_range(gen);
        randomNumbers.insert(num);
    }

    return randomNumbers;
}

// Función para convertir un set en un vector y desordenar los elementos
vector<int> convertAndShuffle(set<int>& numbersSet)
{
    vector<int> numbersVector(numbersSet.begin(), numbersSet.end());
    random_device rd;
    mt19937 gen(rd());
    shuffle(numbersVector.begin(), numbersVector.end(), gen);
    return numbersVector;
}

// Función para generar un conjunto de datos aleatorio sin repetición
vector<int> generateRandomData(int countMin, int countMax, int rangeStart, int rangeEnd)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_count(countMin, countMax);
    int count = dis_count(gen);

    set<int> randomNumbers = generateRandomNumbers(count, rangeStart, rangeEnd);
    return convertAndShuffle(randomNumbers);
}

// Función para generar un conjunto de datos aleatorio con posibilidad de duplicados
vector<int> generateRandomDuplicatesData(int countMin, int countMax, int rangeStart, int rangeEnd)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_count(countMin, countMax);
    int count = dis_count(gen);

    vector<int> randomDuplicatesData(count);
    uniform_int_distribution<int> dis_positive(rangeStart, rangeEnd);

    generate(randomDuplicatesData.begin(), randomDuplicatesData.end(), [&gen, &dis_positive]() {
        return dis_positive(gen);
    });

    return randomDuplicatesData;
}

// Función para generar un conjunto de datos ordenado (ascendente o descendente)
vector<int> generateOrderedData(int countMin, int countMax, int startValue, bool ascending)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_count(countMin, countMax);
    int count = dis_count(gen);

    vector<int> orderedData(count);
    iota(orderedData.begin(), orderedData.end(), startValue);

    if (!ascending)
    {
        reverse(orderedData.begin(), orderedData.end());
    }

    return orderedData;
}

// Función para generar un conjunto de datos con variación de objetos por categoría
vector<vector<int>> generateObjectData(int categoryCount, int objectCountMin, int objectCountMax)
{
    random_device rd;
    mt19937 gen(rd());

    vector<vector<int>> objectData(categoryCount);

    for (int category = 0; category < categoryCount; ++category)
    {
        uniform_int_distribution<int> dis_count(objectCountMin, objectCountMax);
        int objectCount = dis_count(gen);

        set<int> randomNumbers = generateRandomNumbers(objectCount, 1, 1000); // Rango de objetos disponibles
        objectData[category] = convertAndShuffle(randomNumbers);
    }

    return objectData;
}

// Función para generar un conjunto de datos de carrera a partir de un conjunto de objetos
vector<int> generateRaceData(const vector<int>& objectData, bool randomize, bool allowDuplicates, bool ascendingOrder)
{
    vector<int> raceData = objectData;

    if (randomize)
    {
        shuffle(raceData.begin(), raceData.end(), std::mt19937(std::random_device()()));
    }

    if (!allowDuplicates)
    {
        sort(raceData.begin(), raceData.end());
        raceData.erase(unique(raceData.begin(), raceData.end()), raceData.end());
    }

    if (!ascendingOrder)
    {
        reverse(raceData.begin(), raceData.end());
    }

    return raceData;
}

int main() 
{
    // Generar y desordenar el conjunto de datos del tablero de puntaje
    vector<int> randomVectorScore = generateRandomData(90000, 100000, 0, 1000000);
    vector<int> randomDuplicatesScore = generateRandomDuplicatesData(90000, 100000, 0, 1000000);
    vector<int> orderedVectorScore = generateOrderedData(90000, 100000, 1, true);
    vector<int> reverseOrderedVectorScore = generateOrderedData(90000, 100000, 1, false);

    // Generar y desordenar el conjunto de datos para la determinación de caminos entre aldeas
    vector<int> randomVectorRoads = generateRandomData(50000, 70000, 0, 1000000);
    vector<int> randomDuplicatesRoads = generateRandomDuplicatesData(50000, 70000, 0, 1000000);
    vector<int> orderedVectorRoads = generateOrderedData(50000, 70000, 1, true);
    vector<int> reverseOrderedVectorRoads = generateOrderedData(50000, 70000, 1, false);

    // Generar los conjuntos de datos para el dibujo o renderizado de objetos
    int categoryCount = 15;
    int objectCountMin = 500;
    int objectCountMax = 1000;

    vector<vector<int>> objectData = generateObjectData(categoryCount, objectCountMin, objectCountMax);

    // Generar los conjuntos de datos de carrera con las características requeridas
    bool randomize = true;
    bool allowDuplicates = false;
    bool ascendingOrder = true;

    vector<vector<int>> raceData;

    for (const auto& objectSet : objectData)
    {
        vector<int> randomRace = generateRaceData(objectSet, randomize, allowDuplicates, ascendingOrder);
        vector<int> duplicatedRace = generateRaceData(objectSet, randomize, !allowDuplicates, ascendingOrder);
        vector<int> orderedRace = generateRaceData(objectSet, false, allowDuplicates, ascendingOrder);
        vector<int> reverseOrderedRace = generateRaceData(objectSet, false, allowDuplicates, !ascendingOrder);

        raceData.push_back(randomRace);
        raceData.push_back(duplicatedRace);
        raceData.push_back(orderedRace);
        raceData.push_back(reverseOrderedRace);
    }

    cout << "Datos en arreglo 1 " << randomVectorScore.size() << endl;
    cout << "Datos en arreglo 2 " << randomVectorRoads.size() << endl;

    cout << "Carrera de algoritmos" << endl;
    cout << "1. Ascendente." << endl; // true
    cout << "2. Decendiente" << endl; // false
    cout << "Opción elegida: " << endl;
    int opcion;
    cin >> opcion;
    int set = 1;
    // Seleccionar el algoritmo de ordenamiento según la opción ingresada
    switch (opcion) 
    {
        case 1:
            
            // Ejecutar el algoritmo de ordenamiento ascendente con los datos generados para el tablero
            cout << "Carrera con el Tablero:";
            carrera(1, randomVectorScore, true);
            carrera(2, randomDuplicatesScore, true);
            carrera(3, orderedVectorScore, true);
            carrera(4, reverseOrderedVectorScore, true);
            // Ejecutar el algoritmo de ordenamiento ascendente con los datos generados para los caminos
            cout << "Carrera con los posibles Caminos:";
            carrera(1, randomVectorRoads, true);
            carrera(2, randomDuplicatesRoads, true);
            carrera(3, orderedVectorRoads, true);
            carrera(4, reverseOrderedVectorRoads, true);
            cout << "Carrera con categorias:";
            // Realizar las carreras con los conjuntos de datos generados
            
            for (auto& race : raceData)
            {
                bool orden = true;
                carrera(set, race, orden);
                set++;
            }
            break;
        case 2:
            // Ejecutar el algoritmo de ordenamiento descendente con los datos generados para el tablero
            cout << "Carrera con el Tablero:";
            carrera(1, randomVectorScore, false);
            carrera(2, randomDuplicatesScore, false);
            carrera(3, orderedVectorScore, false);
            carrera(4, reverseOrderedVectorScore, false);
            // Ejecutar el algoritmo de ordenamiento ascendente con los datos generados para los caminos
            cout << "Carrera con los posibles Caminos:";
            carrera(1, randomVectorRoads, false);
            carrera(2, randomDuplicatesRoads, false);
            carrera(3, orderedVectorRoads, false);
            carrera(4, reverseOrderedVectorRoads, false);
            break;
        default:
            std::cout << "Opción inválida" << std::endl;
            break;
    }
    return 0;
}