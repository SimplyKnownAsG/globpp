#ifndef GLOBPP_H_INCLUDED
#define GLOBPP_H_INCLUDED

#include <string>
#include <vector>

#ifdef _MSC_VER

#include <windows.h>

#else

#include <dirent.h>
#include <fnmatch.h>

#endif

namespace globpp {

    std::vector<std::string> glob(const std::string& pattern);

    class Glob {
    private:
        std::string _pattern;

        std::string _dir_name;

    public:
        Glob(const std::string& pattern);

        class iterator;

        iterator begin();

        iterator end();

        class iterator {
        private:
            friend class Glob;

            std::string _pattern;

            std::string _dir_name;

            std::string _file_name;

#ifdef _MSC_VER
            bool _ok = false;

            HANDLE _file_handle;

            WIN32_FIND_DATA _find_data;

#else
            DIR* _dir;

            struct dirent* _dir_entry;

#endif
            iterator(const std::string& dir_name, const std::string& pattern);

            iterator();

        public:
            iterator(iterator&& that);

            iterator(const iterator& that) = delete;

            ~iterator();

            iterator& operator++();

            bool operator==(const iterator& that) const;

            bool operator!=(const iterator& that) const;

            std::string& operator*();
        };
    };
}

#endif
