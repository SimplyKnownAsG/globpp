#include "globpp.hpp"

namespace globpp {

#ifdef _MSC_VER

    static const char* DIR_SEP = "\\";

#else

    static const char* DIR_SEP = "/";

#endif

    std::vector<std::string> glob(const std::string& pattern) {
        std::vector<std::string> paths;
        Glob g(pattern);

        for (auto& p : g) {
            paths.push_back(p);
        }

        return paths;
    };

    Glob::Glob(const std::string& pattern) {
        auto last_sep = pattern.find_last_of(DIR_SEP);

        if (last_sep != std::string::npos) {
            this->_dir_name = std::string(pattern.begin(), pattern.begin() + last_sep);
            this->_pattern = std::string(pattern.begin() + last_sep + 1, pattern.end());
        } else {
            this->_dir_name = ".";
            this->_pattern = pattern;
        }
    };

    Glob::iterator Glob::begin() {
        return Glob::iterator(this->_dir_name, this->_pattern);
    };

    Glob::iterator Glob::end() {
        return Glob::iterator();
    };

    std::string& Glob::iterator::operator*() {
        return this->_file_name;
    };

#ifdef _MSC_VER

    Glob::iterator::iterator(const std::string& dir_name, const std::string& pattern)
            : _ok(false)
            , _file_handle(INVALID_HANDLE_VALUE)
            , _file_name() {
        this->_dir_name = dir_name;
        this->_pattern = pattern;
        std::string full_pattern = dir_name + DIR_SEP + pattern;
        this->_file_handle = FindFirstFile(full_pattern.c_str(), &this->_find_data);
        this->_ok = this->_file_handle != INVALID_HANDLE_VALUE;
        if (this->_ok) {
            this->_file_name = this->_dir_name + DIR_SEP + this->_find_data.cFileName;
        }
    };

    Glob::iterator::iterator()
            : _ok(false)
            , _file_handle(INVALID_HANDLE_VALUE)
            , _file_name() {}

    Glob::iterator::iterator(iterator&& that)
            : _ok(that._ok) {
        this->_file_handle = that._file_handle;
        this->_find_data = that._find_data;
        this->_file_name = that._file_name;
        that._file_handle = INVALID_HANDLE_VALUE;
    };

    Glob::iterator::~iterator() {
        if (this->_file_handle != INVALID_HANDLE_VALUE) {
            FindClose(this->_file_handle);
        }
    };

    Glob::iterator& Glob::iterator::operator++() {
        if (this->_file_handle == INVALID_HANDLE_VALUE) {
            return *this;
        }

        this->_ok = FindNextFile(_file_handle, &_find_data) != 0;

        if (this->_ok) {
            this->_file_name = this->_dir_name + DIR_SEP + this->_find_data.cFileName;
        } else {
            this->_file_name = "";
            FindClose(this->_file_handle);
            this->_file_handle = INVALID_HANDLE_VALUE;
        }

        return *this;
    };

    bool Glob::iterator::operator==(const iterator& that) const {
        return this->_file_handle == that._file_handle;
    };

    bool Glob::iterator::operator!=(const iterator& that) const {
        return this->_file_handle != that._file_handle;
    };

#else

    Glob::iterator::iterator(const std::string& dir_name, const std::string& pattern)
            : _dir_name(dir_name)
            , _pattern(pattern) {
        this->_dir = opendir(this->_dir_name.c_str());
        if (this->_dir != 0) {
            this->operator++();
        }
    };

    Glob::iterator::iterator()
            : _dir_name()
            , _pattern()
            , _file_name()
            , _dir(0)
            , _dir_entry(0){};

    Glob::iterator::iterator(iterator&& that)
            : _dir_name(that._dir_name)
            , _pattern(that._pattern)
            , _file_name(that._file_name) {
        this->_dir = that._dir;
        this->_dir_entry = that._dir_entry;
        that._dir = 0;
        that._dir_entry = 0;
    };

    Glob::iterator::~iterator() {
        if (this->_dir != 0) {
            closedir(this->_dir);
        }
    };

    Glob::iterator& Glob::iterator::operator++() {
        if (this->_dir == 0) {
            this->_file_name = "";
            return *this;
        }
        while ((this->_dir_entry = readdir(this->_dir)) != 0) {
            if (!fnmatch(this->_pattern.c_str(),
                         this->_dir_entry->d_name,
                         FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
                this->_file_name = this->_dir_name + DIR_SEP + this->_dir_entry->d_name;
                return *this;
            }
        }
        this->_file_name = "";
        closedir(this->_dir);
        this->_dir = 0;
        return *this;
    };

    bool Glob::iterator::operator==(const iterator& that) const {
        return this->_dir == that._dir && this->_file_name == that._file_name;
    };

    bool Glob::iterator::operator!=(const iterator& that) const {
        return this->_dir != that._dir || this->_file_name != that._file_name;
    };

#endif
}
