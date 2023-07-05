#include <iostream>
#include <string>
#include <random>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;
using std::cout;
using std::endl;

int main() 
{
    // Configuración de la generación de números aleatorios
    random_device rd;
    mt19937 gen(rd());

    // Cantidad de números aleatorios a generar (entre 90.000 y 100.000)
    uniform_int_distribution<int> dis_count(90000, 100000);
    int num_count = dis_count(gen);

    // Generar números aleatorios únicos
    set<int> random_numbers;
    while (random_numbers.size() < num_count)
    {
        uniform_int_distribution<int> dis_range(0, 1000000);
        int num = dis_range(gen);
        random_numbers.insert(num);
    }

    // Convertir el set en un vector y desordenar los números
    vector<int> random_vector(random_numbers.begin(), random_numbers.end());
    shuffle(random_vector.begin(), random_vector.end(), gen);
    
    cout << "Cantidad de valores en la secuencia " << random_vector.size() << endl;

    cout << "Carrera de algoritmos" << endl;
    cout << "1. Ascendente." << endl;
    cout << "2. Decendiente" << endl;
    cout << "Opción elegida: " << endl;
    int opcion;
    cin >> opcion;
    return 0;
}