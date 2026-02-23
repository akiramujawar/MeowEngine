//
// Created by Akira Mujawar on 23/02/26.
//

#ifndef MEOWENGINE_PROFILERMACROS_HPP
#define MEOWENGINE_PROFILERMACROS_HPP

// TODO: Use this and define the custom profileN here
//#include "TracyAPI.hpp"

#ifdef __ENABLE_TRACY__
    #define PROFILE_SCOPE PT_PROFILE_SCOPE
    #define PROFILE_SCOPE_N(x) PT_PROFILE_SCOPE_N(x)
    #define PROFILE_ALLOC(p, size) PT_PROFILE_ALLOC(p, size, 12);
    #define PROFILE_FREE(p) PT_PROFILE_FREE(p, 12);
#else
    #define PROFILE_SCOPE
    #define PROFILE_SCOPE_N(x)
    #define PROFILE_ALLOC(p, size)
    #define PROFILE_FREE(p)
#endif

#endif //MEOWENGINE_PROFILERMACROS_HPP
