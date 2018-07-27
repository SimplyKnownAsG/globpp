#pragma once

#include "globpp/Search.hpp"

#include <stack>
#include <string>
#include <vector>

namespace globpp {

    class Iterator {
    private:
        friend class Glob;

        std::vector<std::string> _parts;

        std::stack<Search> _searches;

        std::string _file_name;

        Iterator(const std::string dir_name, const std::vector<std::string>& parts);

        Iterator();

        bool _push(std::string dir_name);

    public:
        Iterator(Iterator&& that);

        Iterator(const Iterator& that) = delete;

        ~Iterator() = default;

        Iterator& operator++();

        bool operator==(const Iterator& that) const;

        bool operator!=(const Iterator& that) const;

        std::string& operator*();
    };
}
