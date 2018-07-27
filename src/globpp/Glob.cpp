#include "globpp/Glob.hpp"
#include "globpp/Iterator.hpp"
#include "globpp/globpp.hpp"

#include <iostream>
#include <sstream>

namespace globpp {

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
