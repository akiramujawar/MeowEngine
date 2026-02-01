//
// Created by Akira Mujawar on 05/07/22.
//

#include "engine.hpp"

#ifdef __APPLE__
#import <Cocoa/Cocoa.h>
#endif

int main(int, char* []) {

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

    MeowEngine::Engine().Run();

    return 0;
}