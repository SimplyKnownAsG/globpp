#ifndef GLOBPP_H_INCLUDED
#define GLOBPP_H_INCLUDED

#include <cassert>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>

namespace globpp {

    class Glob {
    private:
        bool _ok;
        HANDLE _file_handle;
        WIN32_FIND_DATA _find_data;

    public:
        Glob(const std::string& pattern);

        ~Glob();

        std::string GetFileName() const;

        operator bool() const;

        bool Next();
    };
}

#else

#include <dirent.h>
#include <fnmatch.h>

namespace globpp {

    class Glob {
    private:
        std::string _dir_name;
        std::string _pattern;
        DIR* _dir;
        struct dirent* _dir_entry;

    public:
        Glob(const std::string& pattern);

        ~Glob();

        std::string GetFileName() const;

        operator bool() const;

        bool Next();
    };
}

#endif

namespace globpp {
    std::vector<std::string> glob(const std::string& pattern);
}

#endif
