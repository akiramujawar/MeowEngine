//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_FILESYSTEM_HPP
#define MEOWENGINE_FILESYSTEM_HPP

#include "Path.hpp"
#include "File.hpp"
#include "FileMode.hpp"

namespace MeowEngine::Core::IO::FileSystem {
    // read the directory
    // on editor
    // use the file system to read retrive & show files
    // while showing files it has to create a structure track it
    // this structure later can be used by the world inspector to edit on go
    // other way
    // no structure will be cached specially
    // we open a brand new window for that particular structure. kinda like unreal
    // that way the ui itself can retrieve and keep a cache inside to display the items.
    // file watcher will initiate any changes to re-update the cached files inside ui
    // similar to our selection data, we also select the file and use it to open it.
    class FileSystem {
    public:
        static bool Exists(const Path& path);

        static bool CreateDirectory(const Path& path);
        static bool IsDirectory(const Path& path);
        
        /**
         *
         * @param filePath old path
         * @param directoryToMovePath new path (must be directory)
         * @return
         */
        static bool Move(const Path& filePath, const Path& directoryToMovePath);

        /**
         *
         * @param a File to be removed / replaced
         * @param b New file to be moved overriding file a
         * @return
         */
        static bool Replace(const Path& a, const Path& b);
        
        /**
         *
         * @param path Path of the file to rename (project/abc.xyz). Includes the file name
         * @param name New name for the file (only name)
         * @return
         */
        static bool Rename(const Path& path, const std::string_view& name);
        static bool Remove(const Path& path);

        static std::unique_ptr<File> Open(const Path& path, FileMode mode);
        static void Close();

        static void Read();
        static void Write();

        static size_t FileSize(const Path& path);

        static void Mount();
        static void Unmount();

        static void Resolve(const Path& virtualPath);
    };

} // Core

#endif //MEOWENGINE_FILESYSTEM_HPP
