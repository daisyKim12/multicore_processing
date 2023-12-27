#include "main.h"
#include "hash.h"


int main() {
    // Open source file using ifstream
    std::ifstream srcFile("J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt");
    if (!srcFile.is_open()) {
        std::cerr << "Error: Can not find text file\n";
        return 1;
    }

    // Assign ofstream for temporary file
    std::ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
        return 1;
    }

    // Convert each word in the file to lowercase
    preprocessFile(srcFile, tempFile);

    // Process the first 10 words in the file
    processFirst10Words();

    // Close file streams
    tempFile.close();
    srcFile.close();


    return 0;
}

// Function to convert each word in the file to lowercase
void preprocessFile(std::ifstream& src, std::ofstream& dest) {
    std::string word;
    while (src >> word) {
        for (char& c : word) {
            c = std::tolower(c);
        }

        //Remove special characters
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return !std::isalnum(c);
        }), word.end());

        dest << word << " ";
    }
}

// Function to process the first 10 words in the file
void processFirst10Words() {

    std::ifstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
    }

    std::string word;
    
    for (int i = 1; i <= 10 && tempFile >> word; ++i) {
        std::cout << i << ": " << word << "\n";
    }
    std::cout << "------------------------------------------\n";
}