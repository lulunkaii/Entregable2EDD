#include <iostream>
#include <vector>
#include "utils.h"

/**
 * @class HashTableUsername
 * @brief Clase para gestionar usuarios usando sus nombres de usuario como claves en una tabla hash.
 */
class HashTableUsername {
private:
    std::vector<User> tabla; ///< Vector que almacena los usuarios.
    int size; ///< Tamaño de la tabla hash.
    int current_size; ///< Número de elementos actuales en la tabla.
    User marca_eliminado; ///< Marca especial para indicar eliminaciones.
    CollisionStrategy strategy; ///< Estrategia de resolución de colisiones.

    /**
     * @brief Calcula el hash principal basado en la clave (nombre de usuario).
     * @param key Clave del usuario (nombre de usuario).
     * @return Valor del hash.
     */
    int hashFunction(const std::string &key) { 
        uint64_t base = 31; // Usamos un número primo para evitar colisiones 
        uint64_t mod = 1e9 + 9; // Módulo grande y primo para evitar colisiones y desbordamientos
        uint64_t hashValue = 0; // Inicializamos hash a 0
        uint64_t power = 1; // Inicializamos potencia de la base a 1

        for (char c : key) { // Para cada caracter en key, hacer
            hashValue = (hashValue + (c * power) % mod) % mod; // Polynomial rolling hash function
            power = (power * base) % mod;
        }
        return hashValue % size; // Retorna el string encriptado
    }

    /**
     * @brief Calcula el segundo hash para doble hashing basado en la clave (nombre de usuario).
     * @param key Clave del usuario (nombre de usuario).
     * @return Valor del segundo hash.
     */
    int secondHashFunction(const std::string &key) { 
        uint64_t base = 37; // Cambiamos el número primo 
        uint64_t mod = 1e9 + 7; 
        uint64_t hashValue = 0; 
        uint64_t power = 1; 

        for (char c : key) { 
            hashValue = (hashValue + (c * power) % mod) % mod; // Polynomial rolling hash function
            power = (power * base) % mod;
        }
        return (hashValue % (size - 1)) + 1;
    }

    /**
     * @brief Calcula el índice basado en la estrategia de colisión.
     * @param hash Valor del hash principal.
     * @param step Valor del segundo hash.
     * @param i Número de intentos.
     * @return Índice calculado.
     */
    int hashingMethod(int hash, int step, int i) const {
        if (strategy == LINEAR_PROBING) return (hash + i) % size;
        else if (strategy == QUADRATIC_PROBING) return (hash + i * i) % size;
        else if (strategy == DOUBLE_HASHING) return (hash + i * step) % size;
        return -1; // No debería llegar nunca acá
    }

    /**
     * @brief Comprueba si un número es primo.
     * @param num Número a comprobar.
     * @return true si es primo, false en caso contrario.
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
     * @brief Encuentra el siguiente número primo mayor o igual a num.
     * @param num Número de partida.
     * @return El siguiente número primo.
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
    HashTableUsername(int size, CollisionStrategy strategy) 
        : size(size), current_size(0), strategy(strategy) {
        this->size = nextPrime(size);
        tabla = std::vector<User>(this->size);
        for (int i = 0; i < this->size; i++) {
            tabla[i] = User();
        }
        marca_eliminado.user_name = "<deleted>";
    }

    /**
     * @brief Inserta un usuario en la tabla.
     * @param user Usuario a insertar.
     */
    void insert(User user) {
        if (current_size == size) {
            std::cerr << "Hash Table is full\n";
            return;
        }

        unsigned long long int hash = hashFunction(user.user_name);
        unsigned long long int step = secondHashFunction(user.user_name);
        int i = 0;

        while (i < size) {
            int index = hashingMethod(hash, step, i);
            if (tabla[index].user_name == "" || tabla[index].user_name == "<deleted>") {
                tabla[index] = user;
                ++current_size;
                return;
            }
            ++i;
        }
    }

    /**
     * @brief Busca un usuario por su nombre de usuario.
     * @param user_name Nombre de usuario a buscar.
     * @return true si el usuario se encuentra, false en caso contrario.
     */
    bool search(const std::string &user_name) {
        int hash = hashFunction(user_name);
        int step = secondHashFunction(user_name);
        int i = 0;
        int hashResult;

        while (i < size) {
            hashResult = hashingMethod(hash, step, i);
            if (tabla[hashResult].user_name == user_name) return true;
            if (tabla[hashResult].user_name == "") return false;
            if (tabla[hashResult].user_name == "<deleted>") {
                ++i;
                continue;
            }
            ++i;
        }
        return false;
    }

    /**
     * @brief Elimina un usuario por su nombre de usuario.
     * @param user_name Nombre de usuario a eliminar.
     */
    void remove(const std::string &user_name) {
        int hash = hashFunction(user_name);
        int step = secondHashFunction(user_name);
        int i = 0;
        int hashResult;

        while (i < size) {
            hashResult = hashingMethod(hash, step, i);
            if (tabla[hashResult].user_name == user_name) {
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
