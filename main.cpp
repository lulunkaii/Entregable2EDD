#include <iostream>
#include <string>
#include "chrono"
#include <fstream>
#include <sstream>
#include "hashTableUserID.h"
#include "hashTableUsername.h"

// Función para medir el tiempo de inserción
template <typename HashTableInsert>
double measure_insertion_time(HashTableInsert& table, User user) {
    auto start = std::chrono::high_resolution_clock::now();
    table.insert(user);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

template <typename HashTableSearchID>
double measure_search_time_userID(HashTableSearchID& table, uint64_t userID) {
    std::cout<<table.search(userID)<<std::endl;
    if (table.search(userID) == false)std::cout<<userID<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    table.search(userID);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

template <typename HashTableSearchUsername>
double measure_search_time_username(HashTableSearchUsername& table, std::string username) {
    std::cout<<table.search(username)<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    table.search(username);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

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

    std::string line;
    std::getline(file, line); // quitamos los headers

    // ####################################################### INSERT ###############################################################
    
    // Variables para almacenar los tiempos totales de la funcion insert()
    double total_time_LPUserID_insert = 0, total_time_QPUserID_insert = 0, total_time_DHUserID_insert = 0;
    double total_time_LPUsername_insert = 0, total_time_QPUsername_insert = 0, total_time_DHUsername_insert = 0;

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
    }
    // Impresión de datos totales insertados para comprobar éxito de inserción
    std::cout << "Datos insertados: " << LPtablaUserID.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << QPtablaUserID.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << DHtablaUserID.getCurrentSize() << std::endl;

    std::cout << "Datos insertados: " << LPtablaUsername.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << QPtablaUsername.getCurrentSize() << std::endl;
    std::cout << "Datos insertados: " << DHtablaUsername.getCurrentSize() << std::endl;

    // Guardar resultados en los archivos .csv
    std::ofstream res_hash_cerrado_LP_userID_insert;
    std::ofstream res_hash_cerrado_QP_userID_insert;
    std::ofstream res_hash_cerrado_DH_userID_insert;
    std::ofstream res_hash_cerrado_LP_username_insert;
    std::ofstream res_hash_cerrado_QP_username_insert;
    std::ofstream res_hash_cerrado_DH_username_insert;

    res_hash_cerrado_LP_userID_insert.open("res_hash_cerrado_LP_userID_insert.csv", std::ios::app);
    res_hash_cerrado_LP_userID_insert << experiment_number << ";universities_followers.csv;hashing_cerrado_insert_LPtablaUserID;" << n << ";" << total_time_LPUserID_insert << "\n";
    res_hash_cerrado_LP_userID_insert.close();

    res_hash_cerrado_QP_userID_insert.open("res_hash_cerrado_QP_userID_insert.csv", std::ios::app);
    res_hash_cerrado_QP_userID_insert << experiment_number << ";universities_followers.csv;hashing_cerrado_insert_QPtablaUserID;" << n << ";" << total_time_QPUserID_insert << "\n";
    res_hash_cerrado_QP_userID_insert.close();

    res_hash_cerrado_DH_userID_insert.open("res_hash_cerrado_DH_userID_insert.csv", std::ios::app);
    res_hash_cerrado_DH_userID_insert << experiment_number << ";universities_followers.csv;hashing_cerrado_insert_DHtablaUserID;" << n << ";" << total_time_DHUserID_insert << "\n";
    res_hash_cerrado_DH_userID_insert.close();

    res_hash_cerrado_LP_username_insert.open("res_hash_cerrado_LP_username_insert.csv", std::ios::app);
    res_hash_cerrado_LP_username_insert << experiment_number << ";universities_followers.csv;hashing_cerrado_insert_LPtablaUsername;" << n << ";" << total_time_LPUsername_insert << "\n";
    res_hash_cerrado_LP_username_insert.close();

    res_hash_cerrado_QP_username_insert.open("res_hash_cerrado_QP_username.csv", std::ios::app);
    res_hash_cerrado_QP_username_insert << experiment_number << ";universities_followers.csv;hashing_cerrado_insert_QPtablaUsername;" << n << ";" << total_time_QPUsername_insert << "\n";
    res_hash_cerrado_QP_username_insert.close();

    res_hash_cerrado_DH_username_insert.open("res_hash_cerrado_DH_username_insert.csv", std::ios::app);
    res_hash_cerrado_DH_username_insert << experiment_number << ";universities_followers.csv;hashing_cerrado_insert_DHtablaUsername;" << n << ";" << total_time_DHUsername_insert << "\n";
    res_hash_cerrado_DH_username_insert.close();
    
    // ################################################ SEARCH: DATOS ENCONTRADOS ########################################################

    // Variables para almacenar los tiempos totales de la funcion search()
    double total_time_LPUserID_search_found = 0, total_time_QPUserID_search_found = 0, total_time_DHUserID_search_found = 0;
    double total_time_LPUsername_search_found = 0, total_time_QPUsername_search_found = 0, total_time_DHUsername_search_found = 0;

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
        
        //std::cout<<LPtablaUserID.search(user.user_id)<<std::endl;
        //std::cout<<QPtablaUserID.search(user.user_id)<<std::endl;
        //std::cout<<DHtablaUserID.search(user.user_id)<<std::endl;

        total_time_LPUserID_search_found += measure_search_time_userID(LPtablaUserID, user.user_id);
        //total_time_QPUserID_search_found += measure_search_time_userID(QPtablaUserID, user.user_id);
        //total_time_DHUserID_search_found += measure_search_time_userID(DHtablaUserID, user.user_id);
        
        //total_time_LPUsername_search_found += measure_search_time_username(LPtablaUsername, user.user_name);
        //total_time_QPUsername_search_found += measure_search_time_username(QPtablaUsername, user.user_name);
        //total_time_DHUsername_search_found += measure_search_time_username(DHtablaUsername, user.user_name);
        
        
    }
    /*
    // Guardar resultados en los archivos .csv
    std::ofstream res_hash_cerrado_LP_userID_search_found;
    std::ofstream res_hash_cerrado_QP_userID_search_found;
    std::ofstream res_hash_cerrado_DH_userID_search_found;
    std::ofstream res_hash_cerrado_LP_username_search_found;
    std::ofstream res_hash_cerrado_QP_username_search_found;
    std::ofstream res_hash_cerrado_DH_username_search_found;

    res_hash_cerrado_LP_userID_search_found.open("res_hash_cerrado_LP_userID_search_found.csv", std::ios::app);
    res_hash_cerrado_LP_userID_search_found << experiment_number << ";universities_followers.csv;hashing_cerrado_search_found_LPtablaUserID;" << n << ";" << total_time_LPUserID_search_found << "\n";
    res_hash_cerrado_LP_userID_search_found.close();

    res_hash_cerrado_QP_userID_search_found.open("res_hash_cerrado_QP_userID_search_found.csv", std::ios::app);
    res_hash_cerrado_QP_userID_search_found << experiment_number << ";universities_followers.csv;hashing_cerrado_search_found_QPtablaUserID;" << n << ";" << total_time_QPUserID_search_found << "\n";
    res_hash_cerrado_QP_userID_search_found.close();

    res_hash_cerrado_DH_userID_search_found.open("res_hash_cerrado_DH_userID_search_found.csv", std::ios::app);
    res_hash_cerrado_DH_userID_search_found << experiment_number << ";universities_followers.csv;hashing_cerrado_search_found_DHtablaUserID;" << n << ";" << total_time_DHUserID_search_found << "\n";
    res_hash_cerrado_DH_userID_search_found.close();

    res_hash_cerrado_LP_username_search_found.open("res_hash_cerrado_LP_username_search_found.csv", std::ios::app);
    res_hash_cerrado_LP_username_search_found << experiment_number << ";universities_followers.csv;hashing_cerrado_search_found_LPtablaUsername;" << n << ";" << total_time_LPUsername_search_found << "\n";
    res_hash_cerrado_LP_username_search_found.close();

    res_hash_cerrado_QP_username_search_found.open("res_hash_cerrado_QP_username_search_found.csv", std::ios::app);
    res_hash_cerrado_QP_username_search_found << experiment_number << ";universities_followers.csv;hashing_cerrado_search_found_QPtablaUsername;" << n << ";" << total_time_QPUsername_search_found << "\n";
    res_hash_cerrado_QP_username_search_found.close();

    res_hash_cerrado_DH_username_search_found.open("res_hash_cerrado_DH_username_search_found.csv", std::ios::app);
    res_hash_cerrado_DH_username_search_found << experiment_number << ";universities_followers.csv;hashing_cerrado_search_found_DHtablaUsername;" << n << ";" << total_time_DHUsername_search_found << "\n";
    res_hash_cerrado_DH_username_search_found.close();

    */

    file.close();
    return 0;
}
