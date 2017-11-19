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

static std::pair<std::string, std::string> SplitPath(const std::string& path) {
    std::string::size_type last_sep = path.find_last_of("/");
    if (last_sep != std::string::npos) {
        return std::make_pair(std::string(path.begin(), path.begin() + last_sep),
                              std::string(path.begin() + last_sep + 1, path.end()));
    }
    return std::make_pair(".", path);
}

namespace globpp {

    class Glob {
    private:
        std::string dir_name_;
        std::string pattern_;
        DIR* dir_;
        struct dirent* dir_entry_;

    public:
        Glob(const std::string& pattern)
          : dir_(0)
          , dir_entry_(0) {
            std::pair<std::string, std::string> dir_and_mask = SplitPath(pattern);
            this->dir_name_ = dir_and_mask.first;
            dir_ = opendir(dir_and_mask.first.c_str());
            pattern_ = dir_and_mask.second;

            if (dir_ != 0) {
                Next();
            }
        };

        ~Glob() {
            if (dir_ != 0) {
                closedir(dir_);
            }
        };

        std::string GetFileName(bool full_name = false) const {
            assert(dir_entry_ != 0);
            if (full_name) {
                return this->dir_name_ + "/" + dir_entry_->d_name;
            } else {
                return dir_entry_->d_name;
            }
        }

        operator bool() const {
            return dir_entry_ != 0;
        }

        bool Next() {
            while ((dir_entry_ = readdir(dir_)) != 0) {
                if (!fnmatch(pattern_.c_str(),
                             dir_entry_->d_name,
                             FNM_CASEFOLD | FNM_NOESCAPE | FNM_PERIOD)) {
                    return true;
                }
            }
            return false;
        };
    };
}
#endif

namespace globpp {
    std::vector<std::string> glob(const std::string& pattern, bool full_name = true) {
        std::vector<std::string> paths;
        Glob g(pattern);

        while (g) {
            paths.push_back(g.GetFileName(full_name));
            g.Next();
        }

        return paths;
    };
}
