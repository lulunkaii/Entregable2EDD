#include <iostream>
#include <string>
#include <list>

using namespace std;

// Estructura que define la información del usuario.
struct UserInfo {
    string university;        // Universidad del usuario
    double user_id;           // ID del usuario
    string user_name;         // Nombre del usuario
    int number_tweets;        // Número de tweets del usuario
    int friends_count;        // Cantidad de amigos del usuario
    int followers_count;      // Cantidad de seguidores del usuario
    string created_at;        // Fecha de creación del perfil
};

// Clase que implementa una tabla hash con hashing abierto que toma como clave el user_name del usuario.
class HashOpenUsername {
    public:
        int hashCapacity = 21997;    // Capacidad de la tabla hash. Es un número primo para mejor dispersión.
        int currentSize = 0;         // Tamaño actual (número de elementos) de la tabla hash
        list<UserInfo>* tabla;       // Array de listas. Cada posición del array contiene una lista de UserInfo
        
    public:
        HashOpenUsername();          // Constructor
        void put(string key, UserInfo infoUser);  // Método para insertar un elemento en la tabla hash
        void remove(string key);     // Método para eliminar un elemento de la tabla hash
        bool search(string key);     // Método para buscar si un elemento está en la tabla hash
        int size();                  // Método para obtener el tamaño actual de la tabla hash
        int hashFunction(string key); // Método para calcular el índice hash basado en la clave
        bool isEmpty();              // Método para verificar si la tabla hash está vacía
};