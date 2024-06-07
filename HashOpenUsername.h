#include <iostream>
#include <string>
#include <list>

using namespace std;

struct UserInfo{

    string key;
    string university;
    string user_id;
    string user_name;
    string number_tweets;
    string friends_count;
    string followers_count;
    string created_at;

};

class HashOpenUsername{

    public:
            
            int hashCapacity = 21997;
            int currentSize = 0;
            list<UserInfo>* tabla;
    public:
            HashOpenUsername();
            void put(string key, UserInfo infoUser);
            void remove(string  key);
            string get(string  key);
            bool search(string key);
            int size();
            int hashFunction(string  key);
            bool isEmpty();

};