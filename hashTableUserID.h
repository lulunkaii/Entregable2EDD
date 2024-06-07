#include <iostream>
#include <vector>
#include "utils.h"

/**
 * @class HashTableUserID
 * @brief Clase para gestionar usuarios usando sus IDs como claves en una tabla hash, implementada para usar con las 3 estrategias
 */
class HashTableUserID {
private:
    std::vector<User> tabla; ///< Vector que almacena los usuarios
    int size; ///< Tamaño de la tabla hash
    int current_size; ///< Número de elementos actuales en la tabla
    User marca_eliminado; ///< Marca especial para indicar eliminaciones
    CollisionStrategy strategy; ///< Estrategia de resolución de colisiones

    /**
     * @brief Calcula el hash principal basado en la clave
     * @param key Clave del usuario
     * @return Valor del hash
     */
    int hashFunction(unsigned long long key) {
        return key % size; // Clásico hash por módulo
    }

    /**
     * @brief Calcula el segundo hash para doble hashing
     * @param key Clave del usuario
     * @return Valor del segundo hash
     */
    int secondHashFunction(unsigned long long key) {
        return 1 + (key % (size - 1));
    }

    /**
     * @brief Calcula el índice basado en la estrategia de colisión
     * @param hash Valor del hash principal
     * @param step Valor del segundo hash
     * @param i Número de intentos
     * @return Índice calculado
     */
    int hashingMethod(int hash, int step, int i) const {
        if (strategy == LINEAR_PROBING) return (hash + i) % size;
        else if (strategy == QUADRATIC_PROBING) return (hash + i * i) % size;
        else if (strategy == DOUBLE_HASHING) return (hash + i * step) % size;
        return -1; // No debería llegar nunca acá
    }

    /**
     * @brief Comprueba si un número es primo
     * @param num Número a comprobar
     * @return true si es primo, false en caso contrario
     */
    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }

    /**
     * @brief Encuentra el siguiente número primo mayor o igual a num, para minimizar colisiones
     * @param num Número de partida
     * @return El siguiente número primo
     */
    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

public:
    /**
     * @brief Constructor para inicializar la tabla con la estrategia de colisión.
     * @param size Tamaño inicial de la tabla.
     * @param strategy Estrategia de resolución de colisiones.
     */
    HashTableUserID(int size, CollisionStrategy strategy) 
        : size(size), current_size(0), strategy(strategy) {
        this->size = nextPrime(size + int(size * 0.12)); // Aumenta el tamaño y busca el siguiente primo
        tabla = std::vector<User>(this->size);
        for (int i = 0; i < this->size; i++) {
            tabla[i] = User();
        }
        marca_eliminado.user_id = -1; // Usar un valor único para marcar eliminados
    }

    /**
     * @brief Inserta un usuario en la tabla.
     * @param user Referencia al usuario a insertar.
     */
    void insert(User& user) {
        if (current_size == size) {
            std::cerr << "Hash Table is full\n";
            return;
        }

        int hash = hashFunction(user.user_id);
        int step = secondHashFunction(user.user_id);
        int i = 0;

        while (i < size) {
            int index = hashingMethod(hash, step, i); // Utilizar índice calculado aquí
            if (tabla[index].user_id == 0 || tabla[index].user_id == -1) {
                tabla[index] = user;
                ++current_size;
                return;
            }
            ++i;
        }
    }

    /**
     * @brief Busca un usuario por su ID.
     * @param user_id ID del usuario a buscar.
     * @return true si el usuario se encuentra, false en caso contrario.
     */
    bool search(unsigned long long user_id) {
        unsigned long long hash = hashFunction(user_id);
        unsigned long long int step = secondHashFunction(user_id);
        int i = 0;
        int hashResult;

        while (i < size) {
            hashResult = hashingMethod(hash, step, i);
            if (tabla[hashResult].user_id == user_id) return true;
            if (tabla[hashResult].user_id == 0) return false; 
            if (tabla[hashResult].user_id == -1) {
                ++i;
                continue;
            }
            ++i;
        }
        return false;
    }

    /**
     * @brief Elimina un usuario por su ID.
     * @param user_id ID del usuario a eliminar.
     */
    void remove(unsigned long long user_id) {
        int hash = hashFunction(user_id);
        int step = secondHashFunction(user_id);
        int i = 0;
        int hashResult;

        while (i < size) {
            hashResult = hashingMethod(hash, step, i);
            if (tabla[hashResult].user_id == user_id) {
                tabla[hashResult] = marca_eliminado;
                --current_size;
                return;
            }
            ++i;
        }
        std::cerr << "user not found" << std::endl;
    }

    /**
     * @brief Obtiene el tamaño actual de la tabla.
     * @return Número de elementos actuales en la tabla.
     */
    int getCurrentSize() {
        return current_size;
    }
};
