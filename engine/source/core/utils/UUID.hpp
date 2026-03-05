//
// Created by Akira Mujawar on 03/03/26.
//

#ifndef MEOWENGINE_UUID_HPP
#define MEOWENGINE_UUID_HPP

#include "random"
#include "log.hpp"

namespace MeowEngine::Editor {
    class UUID {
    public:
        static void Generate() {
            MeowEngine::Log("test", GenerateHex(5));
        }
        
    private:
        static unsigned char GetRandomChar() {
            std::random_device device;
            std::mt19937 mt(device());
            std::uniform_int_distribution<> uid(0, 255);
            
            return uid(mt);
        }
        
        static std::string GenerateHex(const unsigned int length) {
            static const char* hexDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVXYX";
            std::string hex;
            hex.reserve(length * 2);
            
            for(int i = 0; i < length; i++) {
                unsigned char character = GetRandomChar();
    
                // high nibble
                hex.push_back(hexDigits[character >> 4]);
                // low nibble
                hex.push_back(hexDigits[character & 0x0F]);
            }
            
            return hex;
        }
    };
}


#endif //MEOWENGINE_UUID_HPP
