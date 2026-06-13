//
// Created by Akira Mujawar on 05/07/22.
//

#include <Engine.hpp>

#if (!WEB)
#ifdef __APPLE__
    #import <Cocoa/Cocoa.h>
#endif
#endif

#import <log.hpp>

void SetApplicationIcon() {
    #if (!WEB)
    #ifdef __APPLE__
        @autoreleasepool {
            NSApplication *app = [NSApplication sharedApplication];

            // This makes it show in Dock
            [app setActivationPolicy:NSApplicationActivationPolicyRegular];

            NSImage *img = [[NSImage alloc] initWithContentsOfFile:@"assets/icons/icon.png"];
            if (img) {
                [app setApplicationIconImage:img];
            }

            // Important: tell macOS we finished startup
            [app finishLaunching];
        }
    #endif
    #endif
}

int main(int, char* []) {
    SetApplicationIcon();
    MeowEngine::Engine().Open();

    return 0;
}