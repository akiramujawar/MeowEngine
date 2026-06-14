//
// Created by Akira Mujawar on 08/07/24.
//

#ifndef MEOWENGINE_TRACYAPI_HPP
#define MEOWENGINE_TRACYAPI_HPP

//#include <TracyOpenGL.hpp>
//#include <Tracy.hpp>
//#include <TracyOpenCL.hpp>
//#include "../../../../../../third-party/tracy/public/common/TracySystem.hpp"

#if (__WEB__)
    #define PT_PROFILE_SCOPE
    #define PT_PROFILE_SCOPE_N(x)
    #define PT_PROFILE_ALLOC(p, size)
    #define PT_PROFILE_FREE(p)
#else
    #include "Tracy.hpp"
    #include "TracyC.h"

    #include <TracyOpenGL.hpp>
    //#include "TracyOpenCL.hpp"
    //#include "TracyOpenGL.hpp"
    #include "../../../../third-party/tracy/public/common/TracySystem.hpp"

    #define PT_PROFILE_SCOPE ZoneScoped
    #define PT_PROFILE_SCOPE_N(x) ZoneScopedN(x)
    #define PT_PROFILE_ALLOC(p, size) TracyCAllocS(p, size, 12);
    #define PT_PROFILE_FREE(p) TracyCFreeS(p, 12);
#endif

//        TracyGpuContext
//        TracyMessageL("Sleep a little bit");
//        TracyMessageL( "Tick" );
//        tracy::SetThreadName( "Message test" );
//        ZoneScoped;
//        TracyGpuZone("this")
//        TracyGpuCollect;
//        FrameMark;
//        TracyAlloc(Window, 5);
//        TracyGpuContext(context, nullptr);
//        TracyGpuContext;
//        TracyGpuZone("x")
//        TracyAppInfo("app_info.data()", "app_info.size()");
//        LUXE_PROFILE_GPU("use program");
//        TracyMessageL("Starting the application");
//        TracyMessageL("Set jobs");


#endif //MEOWENGINE_TRACYAPI_HPP
