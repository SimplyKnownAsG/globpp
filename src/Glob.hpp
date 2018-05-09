#pragma once

#include <string>
#include <vector>

namespace globpp {

    std::vector<std::string> glob(const std::string& pattern);

    class Iterator;

    class Glob {
    private:
        std::vector<std::string> _parts;

    public:
        Glob(const std::string& pattern);

        Iterator begin();

        Iterator end();
    };
}
