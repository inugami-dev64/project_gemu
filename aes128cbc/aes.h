#ifndef AES_H
#define AES_H
#include <vector>
#include <string>

namespace aes {

    std::vector<std::vector<std::vector<unsigned char>>> expandKey(std::string key);
    std::vector<std::vector<std::vector<unsigned char>>> getMessageBlocks(std::string message);
    std::string decrypt(std::vector<std::vector<std::vector<unsigned char>>> keyRounds, std::string cipherText);
    std::string encrypt(std::vector<std::vector<std::vector<unsigned char>>> key, std::vector<std::vector<std::vector<unsigned char>>> message);
}

#endif