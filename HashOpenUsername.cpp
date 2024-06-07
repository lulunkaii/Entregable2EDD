#include <iostream>
#include <sstream>
#include <string>
#include "HashOpenUsername.h"
#include <cmath>

using namespace std;

// Constructor de la clase HashOpenUsername.
HashOpenUsername::HashOpenUsername() {
    // Inicializa la tabla hash.
    tabla = new list<UserInfo>[hashCapacity];
}

// Método para insertar un elemento en la tabla hash.
void HashOpenUsername::put(string key, UserInfo infoUser) {
    int claveHash = hashFunction(key); // Calcula el índice hash para la clave.
    currentSize++;                     // Incrementa el tamaño actual de la tabla.
    tabla[claveHash].push_back(infoUser); // Inserta el elemento en la lista correspondiente al índice hash.
}

// Método para eliminar un elemento de la tabla hash.
void HashOpenUsername::remove(string key) {
    int claveHash = hashFunction(key); // Calcula el índice hash para la clave.
    auto& cell = tabla[claveHash];     // Obtiene la lista correspondiente al índice hash.
    auto Iterador = begin(cell);       // Inicializa el iterador para recorrer la lista.
    bool llaveExiste = false;

    // Recorre la lista buscando el elemento con la clave especificada.
    for (; Iterador != end(cell); Iterador++) {
        if (Iterador->user_name == key) { // Compara con el nombre de usuario.
            llaveExiste = true;
            Iterador = cell.erase(Iterador); // Elimina el elemento de la lista.
            currentSize--;                   // Decrementa el tamaño actual de la tabla.
            break;
        }
    }
}

// Método para buscar un elemento en la tabla hash.
bool HashOpenUsername::search(string key) {
    int claveHash = hashFunction(key); // Calcula el índice hash para la clave.
    int i = 0;  // Contador por si no hay ningun elemento en la tabla

    // Mientras haya elementos en la lista correspondiente y no se haya recorrido toda la capacidad de la tabla.
    while (tabla[claveHash].empty() == false && i < hashCapacity) {
        // Recorre la lista buscando el elemento con la clave especificada.
        for (const auto& IdInfo : tabla[claveHash]) {
            if (IdInfo.user_name == key) { // Compara con el nombre de usuario.
                return true;
            }
        }
        i++;
        claveHash++;
        claveHash %= hashCapacity; // Asegura que el índice hash esté dentro de los límites de la tabla.
    }
    return false;
}

// Función hash para calcular el índice en la tabla hash.
int HashOpenUsername::hashFunction(string key) {
    int sum = 0;

    // Suma los valores ASCII de los caracteres en la clave.
    for (char c : key) {
        sum += static_cast<int>(c);
    }

    // Multiplica la suma por 113 y aplica el operador módulo con la capacidad de la tabla.
    sum = (sum * 113) % hashCapacity;

    return sum;
}

// Método para obtener el tamaño actual de la tabla hash.
int HashOpenUsername::size() {
    return currentSize;
}

// Método para verificar si la tabla hash está vacía.
bool HashOpenUsername::isEmpty() {
    return currentSize == 0;
}