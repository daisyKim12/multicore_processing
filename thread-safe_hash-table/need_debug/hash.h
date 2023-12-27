#ifndef HASH_H
#define HASH_H

#define MAX_WORD_SIZE 101
#define BUCKET_SIZE 437

#include <list>
#include <string>
#include <iostream>
#include <fstream>
// #include <mutex>

#define MUTEX_NUM 4

using namespace std;

class Hash
{

    private:
        int BUCKET; 
        int mutex_num;
        // Pointer to an array containing buckets
        list<string> *table;

        std::mutex mutex_table[4];
        

    public:
        Hash(int num_bucket);

        void insertItem(string word);

        void deleteItem(string key);

        int hashFunction(string str);

        void displayHash(int bucket_num, int link_num, bool print);

};

#endif
