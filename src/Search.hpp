#pragma once

#include <string>

#ifdef _MSC_VER

#include <windows.h>

#else

#include <dirent.h>
#include <fnmatch.h>

#endif

namespace globpp {

    class Search {
    private:
        const std::string _dir_name;

        const std::string _pattern;

#ifdef _MSC_VER
        bool _first;

        HANDLE _file_handle;

#else
        DIR* const _dir;

#endif
    public:
        Search(std::string dir_name, std::string pattern);

        Search(Search&& that) = delete;

        Search(const Search& that) = delete;

        ~Search();

        bool next(std::string& file_name);
    };
}
