#include <iostream>
#include <vector>
#include "utils.h"
    
class HashTableUsername{
    private:
        std::vector<User> tabla;
        int size;
        int current_size;
        User marca_eliminado;
        CollisionStrategy strategy;

    int hashFunction(const std::string &key){ // utilizamos const para no alterar la referencia
        uint64_t base = 31; // usamos un numero primo para evitar colisiones 
        uint64_t mod = 1e9 + 9; // modulo grande y primo para evitar colisiones, desbordamientos
        uint64_t hashValue = 0; // inicializamos hash a 0
        uint64_t power = 1; // inicializamos potencia de la base a 1

        for (char c : key) { // para cada caracter en key, hacer
            hashValue = (hashValue + (c * power) % mod) % mod; // polynomial rollign hash function
            power = (power * base) % mod;
        }
        return hashValue % size; // retorna el string encriptado
    }

    int secondHashFunction(const std::string &key){ 
        uint64_t base = 37; //cambiamos el numero primo 
        uint64_t mod = 1e9 + 7; 
        uint64_t hashValue = 0; 
        uint64_t power = 1; 

        for (char c : key) { 
            hashValue = (hashValue + (c * power) % mod) % mod; // polynomial rollign hash function
            power = (power * base) % mod;
        }
        return (hashValue % (size - 1)) + 1;
    }

    int hashingMethod(int hash, int step, int i) const {
        if (strategy == LINEAR_PROBING) return (hash + i) % size;
        else if (strategy == QUADRATIC_PROBING) return (hash + i * i) % size;
        else if (strategy == DOUBLE_HASHING) return (hash + i * step) % size;
        return -1; // no debería llegar nunca acá
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    public:
        HashTableUsername(int size, CollisionStrategy strategy): size(size), current_size(0), strategy(strategy){
            this->size = nextPrime(size);
            tabla = std::vector<User>(this->size);
            for (int i = 0; i < this->size; i++) {
                tabla[i] = User();
            }
            marca_eliminado.user_name = "<deleted>";
        }
        void insert(User user){
            if (current_size == size) {
                std::cerr << "Hash Table is full\n";
                return;
            }

            int hash = hashFunction(user.user_name);
            int step = secondHashFunction(user.user_name);
            int i = 0;
            while (i < size) { // Establecer un limite máximo de iteraciones
                int index = hashingMethod(hash, step, i);
                if (tabla[index].user_name == "" || tabla[index].user_name == "<deleted>") {
                    // Se encontró una posición vacia por lo que se puede insertar
                    tabla[index] = user;
                    ++current_size;
                    std::cout << "Inserted user at index: " << index << std::endl;
                    return;
                }
                ++i;
            }
            std::cerr << "Failed to insert user: " << user.user_name << " (hash: " << hash << ", step: " << step << "). Reached maximum probing limit.\n";
        }
        bool search(std::string user_name){
            int hash = hashFunction(user_name);
            int step = secondHashFunction(user_name);
            int i = 0;
            int hashResult;

            while (i < size) { 
                hashResult = hashingMethod(hash, step, i);
                if (tabla[hashResult].user_name == user_name) return true;
                else if (tabla[hashResult].user_name == "") return false;
                ++i;
            }
            // recorrió toda la tabla sin encontrar el user
            return false;
        }
        void remove(std::string user_name){
            int hash = hashFunction(user_name);
            int step = secondHashFunction(user_name);
            int i = 0;
            int hashResult;

            while(i<size){
                hashResult = hashingMethod(hash, step, i);
                if (tabla[hashResult].user_name == user_name){
                    tabla[hashResult] = marca_eliminado;
                    --current_size;
                    return;
                }
                ++i;
            }
            //recorrió toda la tabla sin encontrar el user
            std::cerr << "user not found" << std::endl;
        }
        int getCurrentSize(){
            return current_size;
        }
};