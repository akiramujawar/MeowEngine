//
// Created by Akira Mujawar on 22/02/26.
//

#ifndef MEOWENGINE_FILE_HPP
#define MEOWENGINE_FILE_HPP

namespace MeowEngine::Core::IO::FileSystem {

    class File {
    public:
        File();

        bool Open();
        void Close();

        void IsOpen();

        void Size();

        void ReadAll();
        void ReadText();

        void Read();
        void Write();

        void Flush();

        void GetPath();
    };

}


#endif //MEOWENGINE_FILE_HPP
