//
// Created by Akira Mujawar on 29/10/24.
//

#ifndef MEOWENGINE_BUFFER_HPP
#define MEOWENGINE_BUFFER_HPP

#include "utility"
#include "TracyAPI.hpp"

using namespace std;

namespace MeowEngine {
    template <typename T>
    class DoubleBuffer {

    public:
        DoubleBuffer() : Write{}, Read{} {}

        T& GetWrite() {
            return Write;
        }

        T& GetRead() {
            return Read;
        }

        // TODO: rename this to try swap and lock the buffer
        void Swap() {
            PT_PROFILE_SCOPE;
            std::swap(Write, Read);
        }

    protected:
        T Write;
        T Read;
    };
}


#endif //MEOWENGINE_BUFFER_HPP
