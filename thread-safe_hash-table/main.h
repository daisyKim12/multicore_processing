#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <cctype>

void preprocessFile(std::ifstream& src, std::ofstream& dest);
void processFirst10Words();

#endif