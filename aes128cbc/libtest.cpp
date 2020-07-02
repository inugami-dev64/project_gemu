// Example usage of aes library
#include "aes.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    
    std::string mode;
    std::cout << "Would you like to decrypt or encrypt? (d/e)" << std::endl;
    std::getline(std::cin, mode);

    std::string message;
    std::cout << "Enter your message: " << std::endl;
    std::getline(std::cin, message);

    std::string key;
    std::cout << "Enter your encryption key: " << std::endl;
    std::getline(std::cin, key);
    
    // aes::expandKey function that expands key to 11 roundkeys needed for 128bit encryption
    std::vector<std::vector<std::vector<unsigned char>>> roundKeys = aes::expandKey(key);

    std::cout << std::endl;

    if(mode == "e") {
        // aes::getMessageBlocks function that takes message and returns 3D vector of message chars 
        std::vector<std::vector<std::vector<unsigned char>>> mesBlocks = aes::getMessageBlocks(message);
        
        // aes::encrypt function that performs encryption on given messageblocks with given roundkeys
        std::cout << aes::encrypt(roundKeys, mesBlocks) << std::endl;
    }

    else if(mode == "d")
    {   
         // aes::decrypt function that takes encrypted message and decrypts it with given roundkeys
         std::cout << aes::decrypt(roundKeys, message) << std::endl;
    }
    
}
