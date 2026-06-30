//
// Created by Akira Mujawar on 05/01/25.
//

#ifndef MEOWENGINE_TRIPLE_BUFFER_HPP
#define MEOWENGINE_TRIPLE_BUFFER_HPP

#include "utility"

using namespace std;

namespace MeowEngine {
    template <typename T>
    struct TripleBuffer {

    public:
        TripleBuffer() : Write{}, Free{}, Read{} {}

        T& GetWrite() {
            return  Write;
        }

        T& GetFree() {
            return  Free;
        }

        T& GetRead() {
            return  Read;
        }

        // TODO: rename this to try swap and lock the buffer
        // and put it as read / write & free buffers for clear understanding
        void Swap() {
            std::swap(Write, Free);
            std::swap(Write, Read);
        }

    protected:
        T Write;
        T Free;
        T Read;
    };
}


#endif //MEOWENGINE_TRIPLE_BUFFER_HPP
