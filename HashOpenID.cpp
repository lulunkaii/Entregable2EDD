#include <iostream>
#include <sstream>
#include <string>
#include "HashOpenID.h"
#include <cmath>

using namespace std;

HashOpenID::HashOpenID(){

    tabla = new list<IdInfo>[hashCapacity];

    for(int i=0; i< hashCapacity; i++){

        tabla[i].clear();

    }

}

void HashOpenID::put(double key, IdInfo infoUser){

    int claveHash = hashFunction(key);

    currentSize++;

    infoUser.key = key;

    tabla[claveHash].push_back(infoUser);

}

void HashOpenID::remove(double key){

    int claveHash = hashFunction(key);
    auto& cell = tabla[claveHash];
    auto Iterador = begin(cell);
    bool llaveExiste = false;

    for(; Iterador != end(cell);Iterador++){

        if(Iterador->key == key){

            llaveExiste = true;
            Iterador = cell.erase(Iterador);
            currentSize--;
            break;
        }
    }


}

bool HashOpenID::search(double key){

    int claveHash = hashFunction(key);
    int i=0;

    while(tabla[claveHash].empty() == false && i<hashCapacity){

        for(const auto& IdInfo : tabla[claveHash] ){
        
            if (IdInfo.key == key) {

                return true;
            }

        }

        i++;
        claveHash++;
        claveHash %= hashCapacity;

    }

    return false;
}


int HashOpenID::hashFunction(double key){

    return fmod(key,hashCapacity);

}

int HashOpenID::size(){

    return currentSize;

}

bool HashOpenID::isEmpty(){

    if(currentSize == 0){
        return true;
    }

    else return false;

}
