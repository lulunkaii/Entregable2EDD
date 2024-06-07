#include <iostream>
#include <string>
#include <list>

using namespace std;

struct IdInfo{

    double key;
    string university;
    string user_id;
    string user_name;
    string number_tweets;
    string friends_count;
    string followers_count;
    string created_at;

};

class HashOpenID{

    public:
            
            int hashCapacity = 21997;
            int currentSize = 0;
            list<IdInfo>* tabla;
            
    public:
            HashOpenID();
            void put(double key, IdInfo infoUser);
            void remove(double key);
            string get(double key);
            bool search(double key);
            int size();
            int hashFunction(double key);
            bool isEmpty();

};

