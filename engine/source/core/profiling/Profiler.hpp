//
// Created by Akira Mujawar on 23/02/26.
//

#ifndef MEOWENGINE_PROFILER_HPP
#define MEOWENGINE_PROFILER_HPP

#ifdef __ENABLE_TRACY__
    #include "TracyAPI.hpp"
#else
    #define PT_PROFILE_SCOPE
    #define PT_PROFILE_SCOPE_N(x)
    #define PT_PROFILE_ALLOC(p, size)
    #define PT_PROFILE_FREE(p)
#endif

#endif //MEOWENGINE_PROFILER_HPP
