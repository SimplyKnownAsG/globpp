#include "Iterator.hpp"
#include "Search.hpp"

#include <iostream>
#include <sstream>

namespace globpp {

    Iterator::Iterator(const std::string dir_name, const std::vector<std::string>& parts)
            : _parts(parts) {
        if (this->_push(dir_name)) {
            this->operator++();
        }
    }

    bool Iterator::_push(std::string dir_name) {
        std::string pattern = this->_parts.at(this->_searches.size() + 1);
        this->_searches.emplace(dir_name, pattern);
        return true;
    }

    Iterator::Iterator() {}

    Iterator::Iterator(Iterator&& that)
            : _parts(that._parts)
            , _file_name(that._file_name) {
        this->_searches.swap(that._searches);
    }

    Iterator& Iterator::operator++() {
        if (this->_searches.empty()) {
            return *this;
        }

        auto& s = this->_searches.top();

        if (s.next(this->_file_name)) {
            if (this->_searches.size() < this->_parts.size() - 1) {
                this->_push(this->_file_name);
                // recursively call to use the next item in the stack, or try again
                return this->operator++();
            }
            return *this;
        } else {
            this->_file_name = "";
        }

        // recursively call to pop up the stack
        this->_searches.pop();
        return this->operator++();
    }

    bool Iterator::operator==(const Iterator& that) const {
        return this->_searches.size() == that._searches.size() &&
               this->_file_name == that._file_name;
    }

    bool Iterator::operator!=(const Iterator& that) const {
        return this->_searches.size() != that._searches.size() ||
               this->_file_name != that._file_name;
    }
}
