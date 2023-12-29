#include "main.h"


int main() {

    // process text file
    preprocessFile();

    // print the first 10 words in the file
    printFirst10Words();

    std::cout << "------------------------------------------\n";

    Hash ht(BUCKET_SIZE);
    // hashing_thread(ht, THREAD_NUM);

    int thread_num = THREAD_NUM;
    int mutex_num = MUTEX_NUM;
    std::vector<std::thread> threads;
    std::unique_ptr<std::mutex> mutexs(new std::mutex[mutex_num]);
    // https://stackoverflow.com/questions/16465633/how-can-i-use-something-like-stdvectorstdmutex
    // for(int m = 0; m < mutex_num; m++) {
    //     mutexs.push_back(std::mutex());
    // }

    splitFile("temp.txt", "split", thread_num);

    for(int t = 0; t < thread_num; t++) {
        threads.push_back(std::thread(worker, t, thread_num, ht, mutexs));
    }
        
    for (size_t i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }

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

void hashing_thread(Hash hash_table, int thread_num) {

    std::ifstream temp("temp.txt");
    if (!temp.is_open()) {
        std::cerr << "Error: Can not create temp file\n";
    }

    std::string word;
    while (temp >> word) {
        hash_table.insertItem(word);
    }

    temp.close();

}

void worker(int tid, int thread_num, Hash hash_table,  std::unique_ptr<std::mutex> mutexs) {

    std::string file_name = "split/";
    file_name = file_name.append(std::to_string(tid));
    file_name = file_name.append(".txt");

    std::ifstream partition(file_name);
    if (!partition.is_open()) {
        std::cerr << "Error: Can not open " << tid << " file\n";
    }

    std::string word;
    while (partition >> word) {
        hash_table.insertItem(word);
    }

    partition.close();
}

void splitFile(const std::string& inputFileName, const std::string& outputDirectory, int N) {
    std::ifstream inputFile(inputFileName, std::ios::binary | std::ios::ate);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file.\n";
        return;
    }

    std::streampos fileSize = inputFile.tellg();
    std::streampos partSize = fileSize / N;

    // Ensure the output directory exists
    fs::create_directory(outputDirectory);

    for (int i = 0; i < N; ++i) {
        std::ifstream::pos_type start = i * partSize;
        std::ifstream::pos_type end = (i + 1) * partSize;

        // Open output file
        std::string outputFileName = outputDirectory + "/" + std::to_string(i) + ".txt";
        std::ofstream outputFile(outputFileName, std::ios::binary);

        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open output file " << outputFileName << ".\n";
            return;
        }

        // Read and write data
        inputFile.seekg(start);
        std::vector<char> buffer(static_cast<std::size_t>(partSize));
        inputFile.read(buffer.data(), end - start);
        outputFile.write(buffer.data(), end - start);
    }

    inputFile.close();
}