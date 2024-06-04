#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include "hashTableUserID.h"
#include "hashTableUsername.h"


int main(int argc, char** argv) {
    if(argc < 2){
        std::cerr<< "usage:"<< argv[0]<< "cantidad de elementos" << std::endl;
        exit(1);
    } 
    int n = atoi(argv[1]);

    std::ifstream file;
    file.open("universities_followers.csv");

    HashTableUserID LPtablaUserID(n, LINEAR_PROBING);
    HashTableUserID QPtablaUserID(n, QUADRATIC_PROBING);
    HashTableUserID DHtablaUserID(n, DOUBLE_HASHING);

    HashTableUsername LPtablaUsername(n, LINEAR_PROBING);
    HashTableUsername QPtablaUsername(n, QUADRATIC_PROBING);
    HashTableUsername DHtablaUsername(n, DOUBLE_HASHING);

    std::string line;
    std::getline(file, line); // quitamos los headers

    std::cout << "Insert UserID Quadratic Probing " << std::endl;
    // Insertamos n datos del .csv
    for (int i = 0; i < n; i++){
        User user;
        std::getline(file, user.university, ',');
        std::string user_id_str;
        std::getline(file, user_id_str, ',');
        user.user_id = std::stoull(user_id_str); // Convertir la cadena a uint64_t
        std::getline(file, user.user_name, ',');
        std::string number_tweets_str;
        std::getline(file, number_tweets_str, ',');
        user.number_tweets = std::stoull(number_tweets_str); // Convertir la cadena a uint64_t
        std::string friends_count_str;
        std::getline(file, friends_count_str, ',');
        user.friends_count = std::stoi(friends_count_str); // Convertir la cadena a int
        std::string followers_count_str;
        std::getline(file, followers_count_str, ',');
        user.followers_count = std::stoi(followers_count_str); // Convertir la cadena a int
        std::getline(file, user.created_at, '\n');
        
        QPtablaUserID.insert(user);
    }

    // Insertamos los usuarios
    /*
    std::cout<< "Tabla hash de UserID" << std::endl;
    std::cout<< "\tLinear probing" << std::endl;
    for (int i = 0; i < n; i++){
        User user = User();
        user.user_id = i;
        LPtablaUserID.insert(user);
    }

    std::cout<< "\tQuadratic probing" << std::endl;
    for (int i = 0; i < n; i++){
        User user = User();
        user.user_id = i;
        QPtablaUserID.insert(user);
    }

    std::cout<< "\tDouble hashing" << std::endl;
    for (int i = 1; i <= n; i++){
        User user = User();
        user.user_id = i;
        DHtablaUserID.insert(user);
    }
    std::cout<< "total insertados LP:" << LPtablaUsername.getCurrentSize() << std::endl;
    
    
    std::cout<< "Tabla hash de Username" << std::endl;
    std::cout<< "\tLinear probing" << std::endl;
    for (int i = 1; i <= n; i++){
        User user = User();
        user.user_name = std::to_string(i);
        LPtablaUsername.insert(user);
    }
    std::cout<< "total insertados LP:" << LPtablaUsername.getCurrentSize() << std::endl;
    
    
    std::cout<< "\tQuadratic probing" << std::endl;
    for (int i = 1; i <= n; i++){
        User user = User();
        user.user_name = std::to_string(i);
        QPtablaUsername.insert(user);
    }
    std::cout<< "total insertados QP:" << QPtablaUsername.getCurrentSize() << std::endl;
    
    
    std::cout<< "\tDouble hashing" << std::endl;
    for (int i = 1; i <= n; i++){
        User user = User();
        user.user_name = std::to_string(i);
        DHtablaUsername.insert(user);
    }
    std::cout<< "total insertados DH:" << DHtablaUsername.getCurrentSize() << std::endl;
    */
    // Medición de tiempos 



    /*User user1{"universityA", 56, "userA", 100, 200, 300, "2022-01-01"};
    User user2{"universityB", 22, "userB", 150, 250, 350, "2022-02-01"};
    User user3{"universityC", 39, "userC", 200, 300, 400, "2022-03-01"};
    User user4{"universityC", 39, "userC", 200, 300, 400, "2022-03-01"};
    User user5{"universityC", 39, "userC", 200, 300, 400, "2022-03-01"};

    std::cout << "Linear Probing:\n";
    LPtablaUserID.insert(user1);
    LPtablaUserID.insert(user2);
    LPtablaUserID.insert(user3);
    LPtablaUserID.insert(user4);
    LPtablaUserID.insert(user5);
    LPtablaUserID.remove(22);
    LPtablaUserID.insert(user5);
    std::cout << "Searching for user with ID 2 after removal: " << (LPtablaUserID.search(2) ? "Found" : "Not Found") << "\n";
    std::cout << "Searching for user with ID 1: " << (LPtablaUserID.search(1) ? "Found" : "Not Found") << "\n";
    std::cout << "Searching for user with ID 4: " << (LPtablaUserID.search(4) ? "Found" : "Not Found") << "\n";

    LPtablaUserID.remove(2);
    std::cout << "Searching for user with ID 2 after removal: " << (LPtablaUserID.search(2) ? "Found" : "Not Found") << "\n";

    std::cout << "\nQuadratic Probing:\n";
    QPtablaUserID.insert(user1);
    QPtablaUserID.insert(user2);
    QPtablaUserID.insert(user3);
    QPtablaUserID.insert(user4);
    QPtablaUserID.insert(user5);
    std::cout << "Searching for user with ID 22: " << (QPtablaUserID.search(22) ? "Found" : "Not Found") << "\n";
    std::cout << "\nDouble Hashing:\n";
    DHtablaUserID.insert(user1);
    DHtablaUserID.insert(user2);
    DHtablaUserID.insert(user3);
    */
    file.close();
    return 0;
}
