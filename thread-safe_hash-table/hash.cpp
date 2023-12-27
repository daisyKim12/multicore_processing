#include "hash.h"

Hash::Hash(int num_bucket)
{
    this->BUCKET = num_bucket;
    table = new list<string>[BUCKET];
}

void Hash::insertItem(string word)
{
    int index = hashFunction(word);
    table[index].push_back(word); 
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

// function to display hash table
void Hash::displayHash() {
    // for (int i = 0; i < BUCKET; i++) {
    //     cout << i;
    //     for (auto x : table[i])
    //     cout << " --> " << x;
    //     cout << endl;
    // }
}