#include "hash.h"

Hash::Hash(int num_bucket)
{
    this->BUCKET = num_bucket;
    table = new list<string>[BUCKET];
}

void Hash::insertItem(string word)
{
    int index = hashFunction(word);

    auto it = std::find(table[index].begin(), table[index].end(), word);

    if (it == table[index].end()) {
        table[index].push_back(word);
    }
}

void Hash::deleteItem(string word)
{
    // get the hash index of word
    int index = hashFunction(word);

    // define list iterater
    list <string> :: iterator i;
    for (i = table[index].begin();
            i != table[index].end(); i++) {
        if (*i == word)
        break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

int Hash::hashFunction(string str) {

    const char* cstr = str.c_str();
    int bucket_num = BUCKET;
    int hash = 0;

    while(*cstr) {
        hash += *cstr;
        cstr++;
    }

    hash = hash % bucket_num;

    return hash;
}

void Hash::displayHash(int bucket_num, int link_num, bool print) {

    std::ofstream prof("hash_prof.txt");
    if (!prof.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
    }

    for (int i = 0; i < bucket_num; i++) {

        if(!print){

            prof << i << ": ";
            int count = 0;

            for (auto it = table[i].begin(); it != table[i].end() && count < link_num; ++it, ++count) {
                prof << *it << " -> ";
            }

            prof << "...\n";
        } else {
            std::cout << i << ": ";
            int count = 0;

            for (auto it = table[i].begin(); it != table[i].end() && count < link_num; ++it, ++count) {
                std::cout << *it << " -> ";
            }

            std::cout << "..." << std::endl;
        }
        
    }
    
    prof.close();
}
