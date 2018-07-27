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
}
