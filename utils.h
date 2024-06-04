#ifndef UTILS_H
#define UTILS_H
#include <string>

struct User {
    std::string university;
    uint64_t user_id;
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

#endif