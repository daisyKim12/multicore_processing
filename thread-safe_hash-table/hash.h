#ifndef HASH_H
#define HASH_H

#define MAX_WORD_SIZE 101
#define BUCKET_SIZE 437

#include <list>
#include <string>

using namespace std;

class Hash
{

    private:
        int BUCKET; 
        // Pointer to an array containing buckets
        list<string> *table;
        
    public:
        Hash(int num_bucket);

        void insertItem(string word);

        void deleteItem(string key);

        int hashFunction(string str);

        void displayHash();
};

#endif
