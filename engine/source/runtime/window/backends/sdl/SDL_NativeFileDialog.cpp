//
// Created by Akira Mujawar on 28/02/26.
//

#include "SDL_NativeFileDialog.hpp"

#include "SDLAPI.hpp"
#include "NFD_API.hpp"

#include "log.hpp"

namespace {
    void SetNativeWindow(SDL_Window* sdlWindow, nfdwindowhandle_t* nativeWindow) {
        if (!NFD_GetNativeWindowFromSDLWindow(sdlWindow, nativeWindow)) {
            printf("NFD_GetNativeWindowFromSDLWindow failed: %s\n", SDL_GetError());
        }
    }
    
    std::vector<std::string> ShowPaths(const nfdpathset_t* paths, SDL_Window* window, std::vector<std::string>& pathsSelected) {
        size_t num_chars = 0;
        
        nfdpathsetsize_t num_paths;
        if (NFD_PathSet_GetCount(paths, &num_paths) != NFD_OKAY) {
            MeowEngine::Log("NFD_PathSet_GetCount failed", NFD_GetError());
            MeowEngine::Runtime::Window::SDL_NativeFileDialog::ShowMessage(NFD_GetError(), window);

            return pathsSelected;
        }
        
        nfdpathsetsize_t i;
        for (i = 0; i != num_paths; ++i) {
            char* path;
            if (NFD_PathSet_GetPathU8(paths, i, &path) != NFD_OKAY) {
                MeowEngine::Log("NFD_PathSet_GetPathU8 failed", NFD_GetError());
                MeowEngine::Runtime::Window::SDL_NativeFileDialog::ShowMessage(NFD_GetError(), window);

                return pathsSelected;
            }
            num_chars += strlen(path) + 1;
            NFD_PathSet_FreePathU8(path);
        }
        
        // We should never return NFD_OKAY with zero paths, but GCC doesn't know this and will emit a
        // warning that we're trying to malloc with size zero if we write the following line.
        if (!num_paths) {
            num_chars = 1;
        }
        
        for (i = 0; i < num_paths; ++i) {
            char* path = nullptr;
            
            if (NFD_PathSet_GetPathU8(paths, i, &path) != NFD_OKAY) {
                MeowEngine::Log("NFD Error", NFD_GetError());
                MeowEngine::Runtime::Window::SDL_NativeFileDialog::ShowMessage(NFD_GetError(), window);

                return pathsSelected;
            }

            pathsSelected.emplace_back(path);

            NFD_PathSet_FreePathU8(path);
        }

        return pathsSelected;
    }
}

namespace MeowEngine::Runtime::Window {
    void SDL_NativeFileDialog::Init() {
        if (NFD_Init() != NFD_OKAY) {
            throw std::runtime_error("Main Thread:: Could not initialize NFD");
        }
    }
    
    void SDL_NativeFileDialog::Quit() {
        NFD_Quit();
    }
    
    void SDL_NativeFileDialog::ShowError(const char* message, SDL_Window* window) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, window) != 0) {
            printf("SDL_ShowSimpleMessageBox failed: %s\n", SDL_GetError());
            return;
        }
    }
    
    void SDL_NativeFileDialog::ShowMessage(const char* path, SDL_Window* window) {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Success", path, window) != 0) {
                printf("SDL_ShowSimpleMessageBox failed: %s\n", SDL_GetError());
            return;
        }
    }
    
    void SDL_NativeFileDialog::OpenDialog(SDL_Window* window, std::string& path) {
        char* nfdPath;
        nfdopendialogu8args_t args = {0};
        ::SetNativeWindow(window, &args.parentWindow);
        const nfdresult_t res = NFD_OpenDialogU8_With(&nfdPath, &args);
        
        switch (res) {
            case NFD_OKAY:
                path.assign(nfdPath);
                ShowMessage(nfdPath, window);
                NFD_FreePathU8(nfdPath);
                break;
            case NFD_ERROR:
                ShowError(NFD_GetError(), window);
                break;
            default:
                break;
        }
    }
    
    void SDL_NativeFileDialog::OpenDialogMultiple(SDL_Window* window, std::vector<std::string>& paths) {
        const nfdpathset_t* nfdPaths;
        nfdnfilteritem_t filterItem[1] = {
            {
                "Import Types Allowed",
                "png,jpeg,meowdata,obj"
            }
        };
    
        nfdopendialogu8args_t args = {};
        args.filterList = filterItem;
        args.filterCount = 1;
    
        ::SetNativeWindow(window, &args.parentWindow);
    
        const nfdresult_t res = NFD_OpenDialogMultipleU8_With(&nfdPaths, &args);
        switch (res) {
            case NFD_OKAY:
                ShowPaths(nfdPaths, window, paths);
                NFD_PathSet_Free(nfdPaths);

                break;
            case NFD_ERROR:
                ShowError(NFD_GetError(), window);
                break;
            default:
                break;
        }
    }
    
    void SDL_NativeFileDialog::PickFolder(SDL_Window* window, std::string& path) {
        char* nfdPath;
        nfdpickfolderu8args_t args = {0};
        ::SetNativeWindow(window, &args.parentWindow);
        const nfdresult_t res = NFD_PickFolderU8_With(&nfdPath, &args);
        
        switch (res) {
            case NFD_OKAY:
                path.assign(nfdPath);
                ShowMessage(nfdPath, window);
                NFD_FreePathU8(nfdPath);
                break;
            case NFD_ERROR:
                ShowError(NFD_GetError(), window);
                break;
            default:
                break;
        }
    }
    
    void SDL_NativeFileDialog::PickFolderMultiple(SDL_Window* window, std::vector<std::string>& paths) {
        const nfdpathset_t* nfdPaths;
        nfdpickfolderu8args_t args = {0};
        ::SetNativeWindow(window, &args.parentWindow);
        const nfdresult_t res = NFD_PickFolderMultipleU8_With(&nfdPaths, &args);
        
        switch (res) {
            case NFD_OKAY:
                ShowPaths(nfdPaths, window, paths);
                NFD_PathSet_Free(nfdPaths);
                break;
            case NFD_ERROR:
                ShowError(NFD_GetError(), window);
                break;
            default:
                break;
        }
    }

    void SDL_NativeFileDialog::SaveDialog(SDL_Window* window) {
        char* nfdPaths;
        nfdsavedialogu8args_t args = {0};
        ::SetNativeWindow(window, &args.parentWindow);
        const nfdresult_t res = NFD_SaveDialogU8_With(&nfdPaths, &args);

        switch (res) {
            case NFD_OKAY:
                ShowMessage(nfdPaths, window);
                NFD_FreePathU8(nfdPaths);
                break;
            case NFD_ERROR:
                ShowError(NFD_GetError(), window);
                break;
            default:
                break;
        }
    }
    
}
