#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <thread>
#include <cctype>
#include "hash.h"

#define THREAD_NUM 10;

void preprocessFile(void);
void printFirst10Words(void);
void hashing_thread(Hash hash_table);
void worker(int tid, int thread_num, Hash hash_table);
void splitFile(const std::string& inputFileName, const std::string& outputPrefix, int N) ;

#endif