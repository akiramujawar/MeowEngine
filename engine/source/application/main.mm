//
// Created by Akira Mujawar on 05/07/22.
//

#import <AppIcon.hpp>
#import <Engine.hpp>

int main(int, char* []) {
    SetAppIcon();
    MeowEngine::Engine().Open();

    return 0;
}