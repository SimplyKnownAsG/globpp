#include "globpp.hpp"

#ifdef _WIN32

namespace globpp {

    Glob::Glob(const std::string& pattern)
            : _ok(false)
            , _file_handle(INVALID_HANDLE_VALUE) {
        _file_handle = FindFirstFile(pattern.c_str(), &_find_data);
        _ok = _file_handle != INVALID_HANDLE_VALUE;
    };

    Glob::~Glob() {
        if (_file_handle != INVALID_HANDLE_VALUE) {
            FindClose(_file_handle);
        }
    };

    std::string Glob::GetFileName() const {
        assert(_ok);
        return _find_data.cFileName;
    }

    operator Glob::bool() const {
        return _ok;
    }

    bool Glob::Next() {
        _ok = FindNextFile(_file_handle, &_find_data) != 0;
        return _ok;
    };
}

#else

namespace globpp {

    Glob::Glob(const std::string& pattern) {
        auto last_sep = pattern.find_last_of("/");

        if (last_sep != std::string::npos) {
            this->_dir_name = std::string(pattern.begin(), pattern.begin() + last_sep);
            this->_pattern = std::string(pattern.begin() + last_sep + 1, pattern.end());
        } else {
            this->_dir_name = ".";
            this->_pattern = pattern;
        }
    };

    Glob::iterator::iterator(std::string dir_name, std::string pattern)
            : _dir_name(dir_name)
            , _pattern(pattern) {
        this->_dir = opendir(this->_dir_name.c_str());
        if (this->_dir != 0) {
            this->operator++();
        }
    };
}

#endif

namespace globpp {
    std::vector<std::string> glob(const std::string& pattern) {
        std::vector<std::string> paths;
        Glob g(pattern);

        for (auto& p : g) {
            paths.push_back(p);
        }

        /* while (g) { */
        /*     paths.push_back(g.GetFileName()); */
        /*     g.Next(); */
        /* } */

        return paths;
    };
}
