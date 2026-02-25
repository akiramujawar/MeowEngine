//
// Created by Akira Mujawar on 24/02/26.
//

#ifndef MEOWENGINE_FILESTREAM_HPP
#define MEOWENGINE_FILESTREAM_HPP

namespace MeowEngine::Core::IO::FileSystem {

    class FileStream {
    public:
        virtual ~FileStream() = default;

        virtual bool Open();
        virtual void Close();

        virtual void Read();
        virtual void Write();

        virtual void Seek();
        virtual void Tell();

        virtual void IsOpen();
    };

}


#endif //MEOWENGINE_FILESTREAM_HPP
