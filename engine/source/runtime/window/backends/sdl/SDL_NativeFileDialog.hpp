//
// Created by Akira Mujawar on 28/02/26.
//

#ifndef MEOWENGINE_SDL_NATIVEFILEDIALOG_HPP
#define MEOWENGINE_SDL_NATIVEFILEDIALOG_HPP

struct SDL_Window;

namespace MeowEngine::Runtime::Window {
    class SDL_NativeFileDialog {
    public:
        static void Init();
        static void Quit();
        
        static void ShowError(const char* message, SDL_Window* window);
        static void ShowMessage(const char* path, SDL_Window* window);
    
        static void OpenDialog(SDL_Window* window);
        static void OpenDialogMultiple(SDL_Window* window);
        static void SaveDialog(SDL_Window* window);
        static void PickFolder(SDL_Window* window);
        static void PickFolderMultiple(SDL_Window* window);

    };
}

#endif //MEOWENGINE_SDL_NATIVEFILEDIALOG_HPP
