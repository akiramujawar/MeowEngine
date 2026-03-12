// bridge.m
#import <Cocoa/Cocoa.h>
#include <SDL.h>
#import "mac_bridge.h"

void createMacMenu() {
    NSLog(@"Creating macOS menu...");

    @autoreleasepool {
//        NSApplication *app = [NSApplication sharedApplication];
        // Initialize menu bar
        NSMenu *menuContainer = [[NSMenu alloc] init];

        // Allocate menu bar items



        NSApp.mainMenu = menuContainer;

        // Initialize menu bar items




        // ------- MeowEngine
        // Item in main bar
        NSMenuItem *engineApplicationMenuItem = [[NSMenuItem alloc] init];
        [menuContainer addItem:engineApplicationMenuItem];

        // Init menu item in main bar
        NSMenu *engineApplicationMenu = [[NSMenu alloc] initWithTitle:@"Engine Application"];
        [engineApplicationMenuItem setSubmenu:engineApplicationMenu];

        // Add options in menu items
        NSString *appName = [[NSProcessInfo processInfo] processName];
        NSString *quitTitle = [NSString stringWithFormat:@"Quit %@", appName];
        NSMenuItem *quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@"q"];
        [engineApplicationMenu addItem:quitMenuItem];

        // ------ File
        // Item in main bar
        NSMenuItem *fileMenuItem = [[NSMenuItem alloc] init];
        [menuContainer addItem:fileMenuItem];

        // Init menu item in main bar
        NSMenu *fileMenu = [[NSMenu alloc] initWithTitle:@"File"];
        [fileMenuItem setSubmenu:fileMenu];

        // Add options in menu items
        NSMenuItem *saveWorldItem = [[NSMenuItem alloc] initWithTitle:@"Save World" action:@selector(optionSaveWorldAction:) keyEquivalent:@"s"];
        [fileMenu addItem:saveWorldItem];


        // ------ Tools
        // Item in main bar
        NSMenuItem *toolsMenuItem = [[NSMenuItem alloc] init];
        [menuContainer addItem:toolsMenuItem];

        // Init menu item in main bar
        NSMenu *toolsMenu = [[NSMenu alloc] initWithTitle:@"Tools"];
        [toolsMenuItem setSubmenu:toolsMenu];

        // Add options in menu items
        NSMenuItem *openTracyItem = [[NSMenuItem alloc] initWithTitle:@"Open Tracy Profiler" action:@selector(optionOpenTracyProfilerAction:) keyEquivalent:@"1"];
        [toolsMenu addItem:openTracyItem];

    }
    NSLog(@"macOS menu created.");
}

@implementation NSApplication (MenuActions)

- (void)optionOpenTracyProfilerAction:(id)sender {
    NSLog(@"Opening Tracy Profiler");

    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_USEREVENT;
    event.user.code = 1; // UserEventType::OPEN_TRACY
    SDL_PushEvent(&event);
}

- (void)optionSaveWorldAction:(id)sender {
    NSLog(@"Saving World");

    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_USEREVENT;
    event.user.code = 5; // UserEventType::SAVE_PROJECT
    SDL_PushEvent(&event);
}

@end
