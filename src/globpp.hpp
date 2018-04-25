#ifndef GLOBPP_H_INCLUDED
#define GLOBPP_H_INCLUDED

#include <cassert>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>

namespace globpp {

    class Glob {
    public:
        Glob(const std::string& pattern)
          : ok_(false)
          , find_handle_(INVALID_HANDLE_VALUE) {
            find_handle_ = FindFirstFile(pattern.c_str(), &find_data_);
            ok_ = find_handle_ != INVALID_HANDLE_VALUE;
        };

        ~Glob() {
            if (find_handle_ != INVALID_HANDLE_VALUE) {
                FindClose(find_handle_);
            }
        };

        std::string GetFileName() const {
            assert(ok_);
            return find_data_.cFileName;
        }

        operator bool() const {
            return ok_;
        }

        bool Next() {
            ok_ = FindNextFile(find_handle_, &find_data_) != 0;
            return ok_;
        };

    private:
        bool ok_;
        HANDLE find_handle_;
        WIN32_FIND_DATA find_data_;
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
        bool _recursive = false;
        DIR* _dir;
        struct dirent* _dir_entry;

    public:
        Glob(const std::string& pattern)
          : _dir(0)
          , _dir_entry(0) {
            auto last_sep = pattern.find_last_of("/");

            if (last_sep != std::string::npos) {
                this->_dir_name = std::string(pattern.begin(), pattern.begin() + last_sep);
                this->_pattern = std::string(pattern.begin() + last_sep + 1, pattern.end());
            } else {
                this->_dir_name = ".";
                this->_pattern = pattern;
            }

            this->_dir = opendir(this->_dir_name.c_str());

            if (this->_dir != 0) {
                Next();
            }
        };

        ~Glob() {
            if (this->_dir != 0) {
                closedir(this->_dir);
            }
        };

        std::string GetFileName() const {
            assert(this->_dir_entry != 0);
            return this->_dir_name + "/" + this->_dir_entry->d_name;
        }

        operator bool() const {
            return this->_dir_entry != 0;
        }

        bool Next() {
            while ((this->_dir_entry = readdir(this->_dir)) != 0) {
                if (!fnmatch(this->_pattern.c_str(),
                             this->_dir_entry->d_name,
                             FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
                    return true;
                }
                if (this->_recursive && this->_dir_entry->d_type == DT_DIR) {
                }
            }
            return false;
        };
    };
}

#endif

namespace globpp {
    std::vector<std::string> glob(const std::string& pattern) {
        std::vector<std::string> paths;
        Glob g(pattern);

        while (g) {
            paths.push_back(g.GetFileName());
            g.Next();
        }

        return paths;
    };
}

#endif
