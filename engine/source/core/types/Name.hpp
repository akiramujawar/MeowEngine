//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_NAME_HPP
#define MEOWENGINE_NAME_HPP

namespace MeowEngine::Core::Types {
    /**
     * Whenever we want to provide a string version for display but when comparing it's a hashed int
     * Comparing becomes O(1)
     * NOTE: We will not allow modifications once created and enforce using it as a const.
     * Thus the string will be a private set, public get
     */
    class Name {

    };

}


#endif //MEOWENGINE_NAME_HPP
