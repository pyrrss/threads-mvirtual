#ifndef LRUSIMPLE_H
#define LRUSIMPLE_H


#include <iostream>
#include <vector>
using namespace std;

// Función para verificar si una página ya está en memoria
int buscarPagina(const vector<int> &marcos, int pagina) {
    for (int i = 0; i < marcos.size(); i++) {
        if (marcos[i] == pagina) return i;
    }
    return -1;
}

// Función para implementar el algoritmo LRU Reloj Simple
void reemplazoLRU_RelojSimple(vector<int> &marcos, vector<int> &bitsUso, int pagina, int &puntero) {
    while (true) {
        // Si el bit de uso del marco actual es 0, reemplazar la página
        if (bitsUso[puntero] == 0) {
            cout << "Reemplazando página " << marcos[puntero] << " con página " << pagina << endl;
            marcos[puntero] = pagina; // Reemplazar la página
            bitsUso[puntero] = 1;     // Marcar el bit de uso de la nueva página
            puntero = (puntero + 1) % marcos.size(); // Avanzar el puntero
            break;
        } else {
            // Si el bit de uso es 1, ponerlo en 0 y avanzar el puntero
            bitsUso[puntero] = 0;
            puntero = (puntero + 1) % marcos.size();
        }
    }
}


//     int numMarcos, numPaginas;
//     cout << "Ingrese el número de marcos de página: ";
//     cin >> numMarcos;

//     vector<int> marcos(numMarcos, -1); // Inicializar marcos vacíos
//     vector<int> bitsUso(numMarcos, 0); // Inicializar bits de uso en 0
//     int puntero = 0; // Inicializar el puntero al primer marco

//     cout << "Ingrese la cantidad de páginas a cargar: ";
//     cin >> numPaginas;
//     vector<int> paginas(numPaginas);

//     cout << "Ingrese la secuencia de páginas:\n";
//     for (int i = 0; i < numPaginas; i++) {
//         cin >> paginas[i];
//     }

//     int fallos = 0;
//     for (int i = 0; i < numPaginas; i++) {
//         int pagina = paginas[i];
//         cout << "\nAccediendo a la página " << pagina << endl;

//         // Verificar si la página ya está en los marcos
//         int indice = buscarPagina(marcos, pagina);
//         if (indice != -1) {
//             // Página ya está en memoria, actualizar el bit de uso
//             cout << "Página " << pagina << " ya está en memoria." << endl;
//             bitsUso[indice] = 1;
//         } else {
//             // Página no está en memoria, hay que reemplazar
//             cout << "Falló de página." << endl;
//             fallos++;
//             reemplazoLRU_RelojSimple(marcos, bitsUso, pagina, puntero);
//         }

//         // Mostrar el estado actual de los marcos y bits de uso
//         cout << "Marcos actuales: ";
//         for (int j = 0; j < marcos.size(); j++) {
//             if (marcos[j] != -1)
//                 cout << marcos[j] << " ";
//             else
//                 cout << "- ";
//         }
//         cout << "\nBits de uso: ";
//         for (int j = 0; j < bitsUso.size(); j++) {
//             cout << bitsUso[j] << " ";
//         }
//         cout << endl;
//     }

//     cout << "\nTotal de fallos de página: " << fallos << endl;
//     return 0;
// }


#endif