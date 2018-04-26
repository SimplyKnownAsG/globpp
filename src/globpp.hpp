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

    public:
        Glob(const std::string& pattern);

        class iterator {
        private:
            std::string _dir_name;
            std::string _pattern;
            std::string _current_file;
            DIR* _dir;
            struct dirent* _dir_entry;

        public:
            iterator(std::string dir_name, std::string pattern);

            iterator()
                    : _dir_name()
                    , _pattern()
                    , _current_file()
                    , _dir(0)
                    , _dir_entry(0){};

            iterator(iterator&& that)
                    : _dir_name(that._dir_name)
                    , _pattern(that._pattern)
                    , _current_file(that._current_file) {
                this->_dir = that._dir;
                this->_dir_entry = that._dir_entry;
                that._dir = 0;
                that._dir_entry = 0;
            };

            iterator(const iterator& that) = delete;

            ~iterator() {
                if (this->_dir != 0) {
                    closedir(this->_dir);
                }
            };

            iterator& operator++() {
                if (this->_dir == 0) {
                    this->_current_file = "";
                    return *this;
                }
                while ((this->_dir_entry = readdir(this->_dir)) != 0) {
                    if (!fnmatch(this->_pattern.c_str(),
                                 this->_dir_entry->d_name,
                                 FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
                        this->_current_file = this->_dir_name + "/" + this->_dir_entry->d_name;
                        return *this;
                    }
                }
                this->_current_file = "";
                closedir(this->_dir);
                this->_dir = 0;
                return *this;
            };

            bool operator==(const iterator& that) const {
                return this->_dir == that._dir && this->_current_file == that._current_file;
            };

            bool operator!=(const iterator& that) const {
                return this->_dir != that._dir || this->_current_file != that._current_file;
            };

            std::string& operator*() {
                return this->_current_file;
            };
        };

        iterator begin() {
            return iterator(this->_dir_name, this->_pattern);
        };

        iterator end() {
            return iterator();
        };
    };
}

#endif

namespace globpp {
    std::vector<std::string> glob(const std::string& pattern);
}

#endif
