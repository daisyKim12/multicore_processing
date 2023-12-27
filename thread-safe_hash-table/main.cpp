#include "main.h"


int main() {

    // process text file
    preprocessFile();

    // print the first 10 words in the file
    printFirst10Words();

    std::cout << "------------------------------------------\n";

    Hash ht(BUCKET_SIZE);
    hashing_harrypotter(ht);

    ht.displayHash(BUCKET_SIZE, 999, false);

    return 0;
}

// Function to convert each word in the file to lowercase
void preprocessFile(void) {

    // Open source file using ifstream
    std::ifstream src("J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt");
    if (!src.is_open()) {
        std::cerr << "Error: Can not find text file\n";
    }

    // Assign ofstream for temporary file
    std::ofstream temp("temp.txt");
    if (!temp.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
    }

    std::string word;
    while (src >> word) {
        for (char& c : word) {
            c = std::tolower(c);
        }

        //Remove special characters
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return !std::isalnum(c);
        }), word.end());

        temp << word << " ";
    }

    // Close file streams
    temp.close();
    src.close();
}

// Function to process the first 10 words in the file
void printFirst10Words(void) {

    std::ifstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
    }

    std::string word;
    
    for (int i = 1; i <= 10 && tempFile >> word; ++i) {
        std::cout << i << ": " << word << "\n";
    }
}

void hashing_harrypotter(Hash hash_table) {

    std::ifstream temp("temp.txt");
    if (!temp.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
    }

    std::string word;
    while (temp >> word) {
        hash_table.insertItem(word);
    }

    // Close file streams
    temp.close();
}