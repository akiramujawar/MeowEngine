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
        static unsigned char Generate() {
            std::random_device random;
            std::mt19937 mt(random());
            std::uniform_int_distribution<uint64_t> uid;
            
            return uid(mt);
        }
        
        // static std::string GenerateHex(const unsigned int length) {
        //     static const char* hexDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVXYX";
        //     std::string hex;
        //     hex.reserve(length * 2);
        //
        //     for(int i = 0; i < length; i++) {
        //         unsigned char character = GetRandomChar();
        //
        //         // high nibble
        //         hex.push_back(hexDigits[character >> 4]);
        //         // low nibble
        //         hex.push_back(hexDigits[character & 0x0F]);
        //     }
        //
        //     return hex;
        // }
    };
}


#endif //MEOWENGINE_UUID_HPP
