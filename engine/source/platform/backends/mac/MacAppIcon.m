#pragma once

#import "MacAppIcon.h"

#ifdef __APPLE__
    #import <Cocoa/Cocoa.h>

    void SetAppIcon() {
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
    }
#endif
