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
            if (part == "") {
                // This should only happen if the pattern starts with DIR_SEPC (\/)
                if (this->_parts.size() == 0) {
                    // if leading with a /, then add that as the start otherwise gets converted to a
                    // relative directory
                    part = DIR_SEP;
                }

                // XXX: maybe this should be an error..
                /* if (this->_parts.size() > 0) { */
                /*     std::ostringstream err; */
                /*     err << "Unexpected double slash or something in `" << pattern << "`"; */
                /*     throw std::runtime_error(err.str()); */
                /* } */
            }

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
