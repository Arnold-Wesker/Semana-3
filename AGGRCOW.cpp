// En mi caso, implementé una solución que permite maximizar la distancia mínima entre las vacas en los establos. 
// Use mergeSort para ordenar las posiciones de dichos establos, esto me permitió aplicar una búsqueda binaria para 
// hallar la mayor distancia mínima. Por otro lado, la función check verifica si una distancia mínima es psoible, 
// y la función distanciaMinima hace la búsqueda binaria. Todo coordinado desde main, que maneja la entrada y salida de los datos.
#include <iostream>
#include <vector>

using namespace std;

void mergeSort(vector<int>& numeros, int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        mergeSort(numeros, inicio, medio);
        mergeSort(numeros, medio + 1, fin);

        int i = inicio;
        int j = medio + 1;
        int k = 0;

        vector<int> temp(fin - inicio + 1);

        while (i <= medio && j <= fin) {
            if (numeros[i] <= numeros[j]) {
                temp[k++] = numeros[i++];
            } else {
                temp[k++] = numeros[j++];
            }
        }

        while (i <= medio) {
            temp[k++] = numeros[i++];
        }

        while (j <= fin) {
            temp[k++] = numeros[j++];
        }

        for (i = inicio; i <= fin; i++) {
            numeros[i] = temp[i - inicio];
        }
    }
}

bool check(vector<int>& posiciones, int vacas, int minDist) {
    int count = 1;
    int lastPos = posiciones[0];

    for (size_t i = 1; i < posiciones.size(); i++) {
        if (posiciones[i] - lastPos >= minDist) {
            lastPos = posiciones[i];
            count++;
        }

        if (count == vacas) {
            return true;
        }
    }

    return false;
}

int distanciaMinima(vector<int>& posiciones, int vacas) {
    mergeSort(posiciones, 0, posiciones.size() - 1);

    int low = 0;
    int high = posiciones[posiciones.size() - 1] - posiciones[0];
    int resultado = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (check(posiciones, vacas, mid)) {
            resultado = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return resultado;
}

int main() {
    int casosPrueba; 
    cin >> casosPrueba;

   
    for (int i = 0; i < casosPrueba; i++) {
        int numeroEstablos; 
        int numeroVacas; 
        cin >> numeroEstablos >> numeroVacas;

        vector<int> posicionesVacas(numeroEstablos); 
        for (int j = 0; j < numeroEstablos; j++) {
            cin >> posicionesVacas[j];
        }

        int distanciaMinimaResult = distanciaMinima(posicionesVacas, numeroVacas);
        cout << distanciaMinimaResult << endl;
    }

    return 0;
}
