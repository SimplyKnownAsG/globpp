#include "Glob.hpp"
#include "Iterator.hpp"

#include <iostream>
#include <sstream>

namespace globpp {

#ifdef _MSC_VER

    static const char DIR_SEPC = '\\';

#else

    static const char DIR_SEPC = '/';

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
        std::istringstream pattern_stream(pattern);
        std::string part;
        while (std::getline(pattern_stream, part, DIR_SEPC)) {
            this->_parts.push_back(part);
        }
        if (this->_parts.size() == 1) {
            this->_parts.insert(this->_parts.begin(), ".");
        }
    }

    Iterator Glob::begin() {
        return Iterator(this->_parts.at(0), this->_parts);
    }

    Iterator Glob::end() {
        return Iterator();
    }

    std::string& Iterator::operator*() {
        return this->_file_name;
    }
}
