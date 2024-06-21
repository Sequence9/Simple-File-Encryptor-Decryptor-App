#include "FileEncryptor.h"
#include <fstream>
#include <stdexcept>

FileEncryptor::FileEncryptor(const std::string& key) : key(key) {}

void FileEncryptor::encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, std::function<void(int)> progressCallback) {
    processFile(inputFilePath, outputFilePath, true, progressCallback);
}

void FileEncryptor::decryptFile(const std::string& inputFilePath, const std::string& outputFilePath, std::function<void(int)> progressCallback) {
    processFile(inputFilePath, outputFilePath, false, progressCallback);
}

void FileEncryptor::processFile(const std::string& inputFilePath, const std::string& outputFilePath, bool encrypt, std::function<void(int)> progressCallback) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open input file");
    }

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Could not open output file");
    }

    inputFile.seekg(0, std::ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    char inputChar;
    size_t keyIndex = 0;
    size_t processed = 0;

    while (inputFile.get(inputChar)) {
        char keyChar = key[keyIndex];
        char outputChar = xorOperation(inputChar, keyChar);
        outputFile.put(outputChar);
        keyIndex = (keyIndex + 1) % key.size();
        processed++;

        if (progressCallback) {
            progressCallback(static_cast<int>((processed * 100) / fileSize));
        }
    }

    inputFile.close();
    outputFile.close();
}

char FileEncryptor::xorOperation(char inputChar, char keyChar) {
    return inputChar ^ keyChar;
}
