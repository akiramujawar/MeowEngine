//
// Created by Akira Mujawar on 12/03/26.
//

#ifndef MEOWENGINE_USEREVENTTYPE_HPP
#define MEOWENGINE_USEREVENTTYPE_HPP

namespace MeowEngine {
    enum UserEventType : int32_t {
        OPEN_TRACY = 1,
        VIEW_PORT_RESIZE = 2,
        WORLD_VIEW_FOCUS = 3,
        IMPORT_FILE = 4,
        SAVE_PROJECT = 5
    };
}

#endif //MEOWENGINE_USEREVENTTYPE_HPP