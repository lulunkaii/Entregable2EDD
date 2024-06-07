// Leer el README antes de usar. Es la razón del por qué hay código comentado.

#include <iostream>
#include <string>
#include "chrono"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "hashTableUserID.h"
#include "hashTableUsername.h"
#include "hashOpenID.h"
#include "hashOpenUsername.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " cantidad_de_elementos numero_experimento" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]);
    int experiment_number = atoi(argv[2]);

    std::ifstream file;
    file.open("universities_followers.csv");

    HashTableUserID LPtablaUserID(n, LINEAR_PROBING);
    HashTableUserID QPtablaUserID(n, QUADRATIC_PROBING);
    HashTableUserID DHtablaUserID(n, DOUBLE_HASHING);

    HashTableUsername LPtablaUsername(n, LINEAR_PROBING);
    HashTableUsername QPtablaUsername(n, QUADRATIC_PROBING);
    HashTableUsername DHtablaUsername(n, DOUBLE_HASHING);

    HashOpenID hashOpenID;
    HashOpenUsername hashOpenUsername;

    std::unordered_map<uint64_t, User> unordered_map_userID;
    std::unordered_map<std::string, User> unordered_map_username;

    std::string line;
    std::getline(file, line); // quitamos los headers

    // ####################################################### INSERT ###############################################################
    
    // Variables para almacenar los tiempos totales de la funcion insert()
    double total_time_LPUserID_insert = 0, total_time_QPUserID_insert = 0, total_time_DHUserID_insert = 0;
    double total_time_LPUsername_insert = 0, total_time_QPUsername_insert = 0, total_time_DHUsername_insert = 0;
    double total_time_unordered_map_userID_insert = 0, total_time_unordered_map_username_insert = 0;
    double total_time_hashOpenID_insert = 0, total_time_hashOpenUsername_insert = 0;

    // Insertar datos y medir tiempo
    for (int i = 0; i < n; i++) {
        User user;
        std::getline(file, user.university, ',');
        std::string user_id_str;
        std::getline(file, user_id_str, ',');
        user.user_id = std::stoull(user_id_str);
        std::getline(file, user.user_name, ',');
        std::string number_tweets_str;
        std::getline(file, number_tweets_str, ',');
        user.number_tweets = std::stoull(number_tweets_str);
        std::string friends_count_str;
        std::getline(file, friends_count_str, ',');
        user.friends_count = std::stoi(friends_count_str);
        std::string followers_count_str;
        std::getline(file, followers_count_str, ',');
        user.followers_count = std::stoi(followers_count_str);
        std::getline(file, user.created_at, '\n');
        
        total_time_LPUserID_insert += measure_insertion_time(LPtablaUserID, user);
        total_time_QPUserID_insert += measure_insertion_time(QPtablaUserID, user);
        total_time_DHUserID_insert += measure_insertion_time(DHtablaUserID, user);
        
        total_time_LPUsername_insert += measure_insertion_time(LPtablaUsername, user);
        total_time_QPUsername_insert += measure_insertion_time(QPtablaUsername, user);
        total_time_DHUsername_insert += measure_insertion_time(DHtablaUsername, user);
        
        //total_time_hashOpenID_insert += measure_insertion_time(hashOpenID, user);
        //total_time_hashOpenUsername_insert += measure_insertion_time(hashOpenUsername, user);
        
        total_time_unordered_map_userID_insert += measure_insertion_time_unordered_map_userID(unordered_map_userID, user);
        total_time_unordered_map_username_insert += measure_insertion_time_unordered_map_username(unordered_map_username, user);
        
    }
    // Impresión de datos totales insertados para comprobar éxito de inserción
    
    std::cout << "Datos insertados: " << LPtablaUserID.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << QPtablaUserID.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << DHtablaUserID.getCurrentSize() << std::endl;

    std::cout << "Datos insertados: " << LPtablaUsername.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << QPtablaUsername.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << DHtablaUsername.getCurrentSize() << std::endl;
    
    std::cout << "Datos insertados: " << hashOpenID.size() << std::endl;
    std::cout << "Datos insertados: " << hashOpenUsername.size() << std::endl;
    
    // Guardar resultados en el archivo .csv
    std::ofstream resultados;
    resultados.open("resultados.csv", std::ios::app); // Abrir en modo append
    
    resultados << experiment_number << ";universities_followers.csv;LPtablaUserID;" << n << ";" << total_time_LPUserID_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;QPtablaUserID;" << n << ";" << total_time_QPUserID_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;DHtablaUserID;" << n << ";" << total_time_DHUserID_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;LPtablaUsername;" << n << ";" << total_time_LPUsername_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;QPtablaUsername;" << n << ";" << total_time_QPUsername_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;DHtablaUsername;" << n << ";" << total_time_DHUsername_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;unordered_map_userID;" << n << ";" << total_time_unordered_map_userID_insert << "\n";
    resultados << experiment_number << ";universities_followers.csv;unordered_map_username;" << n << ";" << total_time_unordered_map_username_insert << "\n";

    //resultados << experiment_number << ";universities_followers.csv;hashOpenID;" << n << ";" << total_time_hashOpenID_insert << "\n";
    //resultados << experiment_number << ";universities_followers.csv;hashOpenUsername;" << n << ";" << total_time_hashOpenUsername_insert << "\n";
    resultados.close();
    
    // ################################################ SEARCH: DATOS ENCONTRADOS ########################################################

    // Variables para almacenar los tiempos totales de la funcion search()
    double total_time_LPUserID_search_found = 0, total_time_QPUserID_search_found = 0, total_time_DHUserID_search_found = 0;
    double total_time_LPUsername_search_found = 0, total_time_QPUsername_search_found = 0, total_time_DHUsername_search_found = 0;
    double total_time_unordered_map_userID_search_found = 0, total_time_unordered_map_username_search_found = 0;
    double total_time_hashOpenID_search_found = 0, total_time_hashOpenUsername_search_found = 0;
    // Los datos ya fueron insertados anteriormente, por lo que se deberían encontrar
    // Buscar datos y medir tiempo
    file.clear();
    file.seekg(0, std::ios::beg);
    std::getline(file, line); // quitar headers otra vez

    for (int i = 0; i < n; i++) {
        User user;
        std::getline(file, user.university, ',');
        std::string user_id_str;
        std::getline(file, user_id_str, ',');
        user.user_id = std::stoull(user_id_str);
        std::getline(file, user.user_name, ',');
        std::string number_tweets_str;
        std::getline(file, number_tweets_str, ',');
        user.number_tweets = std::stoull(number_tweets_str);
        std::string friends_count_str;
        std::getline(file, friends_count_str, ',');
        user.friends_count = std::stoi(friends_count_str);
        std::string followers_count_str;
        std::getline(file, followers_count_str, ',');
        user.followers_count = std::stoi(followers_count_str);
        std::getline(file, user.created_at, '\n');
        
        total_time_LPUserID_search_found += measure_search_time_userID(LPtablaUserID, user.user_id);
        total_time_QPUserID_search_found += measure_search_time_userID(QPtablaUserID, user.user_id);
        total_time_DHUserID_search_found += measure_search_time_userID(DHtablaUserID, user.user_id);
        
        total_time_LPUsername_search_found += measure_search_time_username(LPtablaUsername, user.user_name);
        total_time_QPUsername_search_found += measure_search_time_username(QPtablaUsername, user.user_name);
        total_time_DHUsername_search_found += measure_search_time_username(DHtablaUsername, user.user_name);
        
        //total_time_hashOpenID_search_found += measure_search_time_userID(hashOpenID, user.user_id);
        //total_time_hashOpenUsername_search_found += measure_search_time_username(hashOpenUsername, user.user_name);
        
        total_time_unordered_map_userID_search_found += measure_search_time_userID_unordered_map(unordered_map_userID, user.user_id);
        total_time_unordered_map_userID_search_found += measure_search_time_username_unordered_map(unordered_map_username, user.user_name);
        
    }

    // Guardar resultados en el archivo .csv
    resultados.open("resultados.csv", std::ios::app);
    
    resultados << experiment_number << ";universities_followers.csv;LPtablaUserID_search_found;" << n << ";" << total_time_LPUserID_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;QPtablaUserID_search_found;" << n << ";" << total_time_QPUserID_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;DHtablaUserID_search_found;" << n << ";" << total_time_DHUserID_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;LPtablaUsername_search_found;" << n << ";" << total_time_LPUsername_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;QPtablaUsername_search_found;" << n << ";" << total_time_QPUsername_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;DHtablaUsername_search_found;" << n << ";" << total_time_DHUsername_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;unordered_map_userID_search_found;" << n << ";" << total_time_unordered_map_userID_search_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;unordered_map_username_search_found;" << n << ";" << total_time_unordered_map_username_search_found << "\n";
    
    //resultados << experiment_number << ";universities_followers.csv;hashOpenID_search_found;" << n << ";" << total_time_hashOpenID_search_found << "\n";
    //resultados << experiment_number << ";universities_followers.csv;hashOpenUsername_search_found;" << n << ";" << total_time_hashOpenUsername_search_found << "\n";
    resultados.close();
    
// ################################################ SEARCH: NOT FOUND ########################################################

    // Variables para almacenar los tiempos totales de la funcion search()
    double total_time_LPUserID_search_NOT_found = 0, total_time_QPUserID_search_NOT_found = 0, total_time_DHUserID_search_NOT_found = 0;
    double total_time_LPUsername_search_NOT_found = 0, total_time_QPUsername_search_NOT_found = 0, total_time_DHUsername_search_NOT_found = 0;
    double total_time_unordered_map_userID_search_NOT_found = 0, total_time_unordered_map_username_search_NOT_found = 0;
    double total_time_hashOpenID_search_NOT_found = 0, total_time_hashOpenUsername_search_NOT_found = 0;
    // Los datos ya fueron insertados anteriormente, por lo que se deberían encontrar
    // Buscar datos y medir tiempo
    file.clear();
    file.seekg(0, std::ios::beg);
    std::getline(file, line); // quitar headers otra vez

    for (int i = 0; i < n; i++) {
        
        total_time_LPUserID_search_NOT_found += measure_search_time_userID(LPtablaUserID, i*-1);
        total_time_QPUserID_search_NOT_found += measure_search_time_userID(QPtablaUserID, i*-1);
        total_time_DHUserID_search_NOT_found += measure_search_time_userID(DHtablaUserID, i*-1);
        
        total_time_LPUsername_search_NOT_found += measure_search_time_username(LPtablaUsername, std::to_string(i));
        total_time_QPUsername_search_NOT_found += measure_search_time_username(QPtablaUsername, std::to_string(i));
        total_time_DHUsername_search_NOT_found += measure_search_time_username(DHtablaUsername, std::to_string(i));
        
        //total_time_hashOpenID_search_NOT_found += measure_search_time_userID(hashOpenID, i*-1);
        //total_time_hashOpenUsername_search_NOT_found += measure_search_time_username(hashOpenUsername, std::to_string(i));
        
        total_time_unordered_map_userID_search_NOT_found += measure_search_time_userID_unordered_map(unordered_map_userID, i*-1);
        total_time_unordered_map_userID_search_NOT_found += measure_search_time_username_unordered_map(unordered_map_username, std::to_string(i));
        
    }

    // Guardar resultados en el archivo .csv
    resultados.open("resultados.csv", std::ios::app);
    
    resultados << experiment_number << ";universities_followers.csv;LPtablaUserID_search_NOT_found;" << n << ";" << total_time_LPUserID_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;QPtablaUserID_search_NOT_found;" << n << ";" << total_time_QPUserID_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;DHtablaUserID_search_NOT_found;" << n << ";" << total_time_DHUserID_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;LPtablaUsername_search_NOT_found;" << n << ";" << total_time_LPUsername_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;QPtablaUsername_search_NOT_found;" << n << ";" << total_time_QPUsername_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;DHtablaUsername_search_NOT_found;" << n << ";" << total_time_DHUsername_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;unordered_map_userID_search_NOT_found;" << n << ";" << total_time_unordered_map_userID_search_NOT_found << "\n";
    resultados << experiment_number << ";universities_followers.csv;unordered_map_username_search_NOT_found;" << n << ";" << total_time_unordered_map_username_search_NOT_found << "\n";
    //resultados << experiment_number << ";universities_followers.csv;hashOpenID_search_NOT_found;" << n << ";" << total_time_hashOpenID_search_NOT_found << "\n";
    //resultados << experiment_number << ";universities_followers.csv;hashOpenUsername_search_NOT_found;" << n << ";" << total_time_hashOpenUsername_search_NOT_found << "\n";
    resultados.close();
    
    file.close();
    return 0;
}
