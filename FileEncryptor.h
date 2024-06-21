#ifndef FILEENCRYPTOR_H
#define FILEENCRYPTOR_H

#include <string>
#include <functional>

class FileEncryptor {
private:
    std::string key;

public:
    FileEncryptor(const std::string& key);
    void encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, std::function<void(int)> progressCallback);
    void decryptFile(const std::string& inputFilePath, const std::string& outputFilePath, std::function<void(int)> progressCallback);

private:
    void processFile(const std::string& inputFilePath, const std::string& outputFilePath, bool encrypt, std::function<void(int)> progressCallback);
    char xorOperation(char inputChar, char keyChar);
};

#endif // FILEENCRYPTOR_H
