#pragma once

#include <string>
#include <vector>

namespace globpp {

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
