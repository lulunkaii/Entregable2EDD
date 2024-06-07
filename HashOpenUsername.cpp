#include <iostream>
#include <sstream>
#include <string>
#include "HashOpenUsername.h"
#include <cmath>


using namespace std;

HashOpenUsername::HashOpenUsername(){

    tabla = new list<UserInfo>[hashCapacity];

    for(int i=0; i< hashCapacity; i++){

        tabla[i].clear();

    }

    
}


void HashOpenUsername::put(string key, UserInfo infoUser){

    int claveHash = hashFunction(key);

    currentSize++;

    infoUser.key = key;

    tabla[claveHash].push_back(infoUser);

}

void HashOpenUsername::remove(string key){

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


bool HashOpenUsername::search(string key){

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


int HashOpenUsername::hashFunction(string key){

    int sum = 0;

    for (char c : key) {
        sum += static_cast<int>(c);
    }

    sum = (sum*113)%hashCapacity;

    return sum;

}

int HashOpenUsername::size(){

    return currentSize;

}

bool HashOpenUsername::isEmpty(){

    if(currentSize == 0){
        return true;
    }

    else return false;

}
