#pragma once

#include <string>
#include <vector>

namespace globpp {

    extern const char DIR_SEPC;

    extern const char* DIR_SEP;

    std::vector<std::string> glob(const std::string& pattern);

    std::string get_current_executable();

    std::string dirname(const std::string& path);

    std::string join(const std::string& p0, const std::string& p1);

    template<typename... Targs>
    std::string join(const std::string& p0, const std::string& p1, Targs... args) {
        // unraveling Targs magic, forces all Targs to be std::string
        std::string start = join(join(p0, p1), args...);
        return start;
    }
}
