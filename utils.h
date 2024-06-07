#ifndef UTILS_H
#define UTILS_H
#include <string>

struct User {
    std::string university;
    unsigned long long user_id;
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;

    User(): university(""), user_id(0), user_name(""), number_tweets(0), friends_count(0), followers_count(0), created_at("") {}
    User(std::string university, uint64_t user_id, std::string user_name, uint64_t number_tweets, uint64_t friends_count, uint64_t followers_count, std::string created_at):
        university(university), user_id(user_id), user_name(user_name), number_tweets(number_tweets), friends_count(friends_count), followers_count(followers_count), created_at(created_at) {}
};  

enum CollisionStrategy {
            LINEAR_PROBING,
            QUADRATIC_PROBING,
            DOUBLE_HASHING
        };

// Función para dividir una cadena por coma y devolver un vector de campos
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

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
    auto start = std::chrono::high_resolution_clock::now();
    table.search(userID);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

template <typename HashTableSearchUsername>
double measure_search_time_username(HashTableSearchUsername& table, std::string username) {
    auto start = std::chrono::high_resolution_clock::now();
    table.search(username);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

// Especificar las funciones para unordered_map
double measure_insertion_time_unordered_map_userID(std::unordered_map<uint64_t, User>& map, const User& user) {
    auto start = std::chrono::high_resolution_clock::now();
    map[user.user_id] = user;
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

double measure_insertion_time_unordered_map_username(std::unordered_map<std::string, User>& map, const User& user) {
    auto start = std::chrono::high_resolution_clock::now();
    map[user.user_name] = user;
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

double measure_search_time_userID_unordered_map(std::unordered_map<uint64_t, User>& map, uint64_t userID) {
    auto start = std::chrono::high_resolution_clock::now();
    auto it = map.find(userID);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

double measure_search_time_username_unordered_map(std::unordered_map<std::string, User>& map, const std::string& username) {
    auto start = std::chrono::high_resolution_clock::now();
    auto it = map.find(username);
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return running_time * 1e-9;
}

#endif