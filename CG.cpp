// En mi caso, use mergesort para ordenar los elementos del array. Para cada elemento de dicho array, hice una copia del array sin 
// ese elemento y la ordené. Luego, mientras mi score sea mayor o igual al primer elemento del array, lo elimino y sumo su valor 
// a mi score. Este número de elementos eliminados se guarda en un array llamado resultados. Finalmente, en la función main, mostre 
// estos resultados. Esto maximiza la cantidad de elementos que se pueden eliminar del array.
#include <iostream>
#include <vector>
using namespace std;

void mergesort(vector<long long>& arr, int izq, int der) {
    if (der - izq <= 1) {
        return;
    }
    int med = izq + (der - izq) / 2;
    mergesort(arr, izq, med);
    mergesort(arr, med, der);
    vector<long long> temp(der - izq);
    int i = izq, j = med, k = 0;
    while (i < med && j < der) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i < med) {
        temp[k++] = arr[i++];
    }
    while (j < der) {
        temp[k++] = arr[j++];
    }
    for (i = izq; i < der; ++i) {
        arr[i] = temp[i - izq];
    }
}

vector<int> solve(vector<long long> a) {
    int n = a.size();
    vector<int> resultados(n);
    for (int i = 0; i < n; ++i) {
        vector<long long> elementos(a.begin(), a.end());
        elementos.erase(elementos.begin() + i);
        mergesort(elementos, 0, elementos.size());
        long long score = a[i];
        int count = 0;
        while (!elementos.empty()) {
            if (elementos.front() <= score) {
                score += elementos.front();
                elementos.erase(elementos.begin());
                ++count;
            } else {
                break;
            }
        }
        resultados[i] = count;
    }
    return resultados;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        vector<int> resultados = solve(a);
        for (int resultado : resultados) {
            cout << resultado << " ";
        }
        cout << endl;
    }
    return 0;
}
