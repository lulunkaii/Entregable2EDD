#include <iostream>
#include <string>
#include <list>

using namespace std;

// Estructura que define la información del usuario.
struct IdInfo {
    string university;       // Universidad del usuario
    double user_id;          // ID del usuario 
    string user_name;        // Nombre del usuario
    int number_tweets;       // Número de tweets del usuario
    int friends_count;       // Cantidad de amigos del usuario
    int followers_count;     // Cantidad de seguidores del usuario
    string created_at;       // Fecha de creación del perfil
};

// Clase que implementa una tabla hash con hashing abierto que toma como clave el user_id del usuario.
class HashOpenID {
    private:
        int hashCapacity = 21997;   // Capacidad de la tabla hash. Es un número primo para mejor dispersión
        int currentSize = 0;        // Tamaño actual (número de elementos) de la tabla hash
        list<IdInfo>* tabla;        // Array de listas. Cada posición del array contiene una lista de IdInfo
        int hashFunction(double key);  // Método para calcular el índice hash basado en la clave

    public:
        HashOpenID();               // Constructor
        void put(double key, IdInfo infoUser);  // Método para insertar un elemento en la tabla hash
        void remove(double key);    // Método para eliminar un elemento de la tabla hash
        bool search(double key);    // Método para buscar si un elemento está en la tabla hash
        int size();                 // Método para obtener el tamaño actual de la tabla hash
        bool isEmpty();             // Método para verificar si la tabla hash está vacía
};

