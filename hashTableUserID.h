#include <iostream>
#include <vector>
#include "utils.h"

class HashTableUserID{
    private:
        std::vector<User> tabla;
        int size;
        int current_size;
        User marca_eliminado;
        CollisionStrategy strategy;

    int hashFunction(unsigned long long key){
        return key % size; // clásico hash por módulo
    }

        int secondHashFunction(unsigned long long key){
        return 1 + (key % (size - 1)); 
    }

    int hashingMethod(int hash, int step, int i) const {
        if (strategy == LINEAR_PROBING) return (hash++) % size;
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
        HashTableUserID(int size, CollisionStrategy strategy): size(size), current_size(0), strategy(strategy){
            this->size = nextPrime(size + int(size*0.12));
            tabla = std::vector<User>(this->size);
            for (int i = 0; i < this->size; i++) {
                tabla[i] = User();
            }
            marca_eliminado.user_id = -1; // Usar un valor único para marcar eliminados
        }
        void insert(User& user){
            if (current_size == size) {
                std::cerr << "Hash Table is full\n";
                return;
            }

            int hash = hashFunction(user.user_id);
            int step = secondHashFunction(user.user_id);
            int i = 1;

            while (i < size) {
                int index = hashingMethod(hash, step, i); // Utilizar index calculado aquí
                if (tabla[index].user_id == 0 || tabla[index].user_id == -1) {
                    tabla[index] = user;
                    ++current_size;
                    return;
                }
                ++i;
            }
        }
        bool search(unsigned long long user_id){
            unsigned long long int hash = hashFunction(user_id);
            unsigned long long int step = secondHashFunction(user_id);
            int i = 0;
            unsigned long long int hashResult;

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
        void remove(unsigned long long user_id){
            int hash = hashFunction(user_id);
            int step = secondHashFunction(user_id);
            int i = 0;
            int hashResult;

            while(i<size){
                hashResult = hashingMethod(hash, step, i);
                if (tabla[hashResult].user_id == user_id){
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