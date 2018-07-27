#include "globpp/Search.hpp"
#include "globpp/globpp.hpp"

#include <sstream>

namespace globpp {

#ifdef _MSC_VER
    Search::Search(std::string dir_name, std::string pattern)
            : _dir_name(dir_name)
            , _pattern(pattern)
            , _first(true)
            , _file_handle(INVALID_HANDLE_VALUE) {}

    Search::~Search() {
        if (this->_file_handle != INVALID_HANDLE_VALUE) {
            FindClose(this->_file_handle);
        }
    }

    bool Search::next(std::string& file_name) {
        WIN32_FIND_DATA find_data;
        bool ok = false;

        if (this->_first) {
            this->_first = false;
            std::string full_pattern = this->_dir_name + DIR_SEP + this->_pattern;
            this->_file_handle = FindFirstFile(full_pattern.c_str(), &find_data);
            ok = this->_file_handle != INVALID_HANDLE_VALUE;
        } else {
            ok = FindNextFile(this->_file_handle, &find_data);
        }

        if (ok) {
            file_name = this->_dir_name + DIR_SEP + find_data.cFileName;
        }

        return ok;
    }

#else
    Search::Search(std::string dir_name, std::string pattern)
            : _dir_name(dir_name)
            , _pattern(pattern)
            , _dir(opendir(dir_name.c_str())) {}

    Search::~Search() {
        if (this->_dir != nullptr) {
            closedir(this->_dir);
        }
    }

    bool Search::next(std::string& file_name) {
        if (this->_dir != nullptr) {
            struct dirent* dir_entry = nullptr;

            while ((dir_entry = readdir(this->_dir)) != nullptr) {
                if (!fnmatch(this->_pattern.c_str(),
                             dir_entry->d_name,
                             FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
                    file_name = this->_dir_name + DIR_SEP + dir_entry->d_name;
                    return true;
                }
            }
        }

        return false;
    }

#endif
}
