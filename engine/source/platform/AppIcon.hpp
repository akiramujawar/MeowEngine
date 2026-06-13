//
// Created by Akira Mujawar on 13/06/26.
//

#ifndef MEOWENGINE_APPICON_HPP
#define MEOWENGINE_APPICON_HPP

#if __WEB__
    void SetAppIcon() {}
#elif __APPLE__
    extern "C" {
        #include "MacAppIcon.h"
    }
#endif

#endif //MEOWENGINE_APPICON_HPP