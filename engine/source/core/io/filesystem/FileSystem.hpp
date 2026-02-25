//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_IO_HPP
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
        static bool Exists(const Path& pPath);

        static bool CreateDirectory(const Path& pPath);
        static bool Remove(const Path&);

        static std::unique_ptr<File> Open(const Path& pPath, FileMode pMode);
        static void Close();

        static void Read();
        static void Write();

        static size_t FileSize(const Path& pPath);

        static void Mount();
        static void Unmount();

        static void Resolve(const Path& pVirtualPath);
    };

} // Core

#endif //MEOWENGINE_IO_HPP
