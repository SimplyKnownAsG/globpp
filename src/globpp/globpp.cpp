#include "globpp/globpp.hpp"
#include "globpp/Glob.hpp"
#include "globpp/Iterator.hpp"

#include <limits.h>
#include <stdexcept>

#ifdef _WIN32

#include "Windows.h"
namespace globpp {
    extern const char DIR_SEPC = '\\';
    extern const char* DIR_SEP = "\\";
}

#elif __APPLE__

#include <libgen.h>
#include <mach-o/dyld.h>
#include <unistd.h>
namespace globpp {
    extern const char DIR_SEPC = '/';
    extern const char* DIR_SEP = "/";
}

#else

#include <libgen.h>
#include <unistd.h>
namespace globpp {
    extern const char DIR_SEPC = '/';
    extern const char* DIR_SEP = "/";
}

#endif

namespace globpp {

    std::vector<std::string> glob(const std::string& pattern) {
        std::vector<std::string> paths;
        Glob g(pattern);

        for (auto& p : g) {
            paths.push_back(p);
        }

        return paths;
    }

    std::string get_current_executable() {
        char path[PATH_MAX + 1];
        uint32_t size = sizeof(path);

#ifdef _WIN32

        if (GetModuleFileName(NULL, path, size) == 0) {
            throw std::runtime_error("Could not determine path of current executable.");
        }

#elif __APPLE__

        if (_NSGetExecutablePath(path, &size) != 0) {
            throw std::runtime_error("Could not determine path of current executable.");
        }

#else

        if (readlink("/proc/self/exe", path, size) < 0) {
            throw std::runtime_error("Could not determine path of current executable.");
        }

#endif
        std::string result(path);

        return result;
    }

    std::string dirname(const std::string& path) {
        auto index = path.find_last_of(DIR_SEP);
        return path.substr(0, index);
    }

    std::string join(const std::string& p0, const std::string& p1) {
        return p0 + DIR_SEP + p1;
    }
}
