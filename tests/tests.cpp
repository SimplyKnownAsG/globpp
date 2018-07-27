#include "catch.hpp"

#include "TempFile.hpp"
#include "globpp/Glob.hpp"
#include "globpp/globpp.hpp"

#include <iostream>

void print_results(std::vector<std::string> results) {
    int num = 0;
    for (auto res : results) {
        std::cout << num++ << "   " << res << std::endl;
    }
}

TEST_CASE("files in current dir", "[tests]") {

    SECTION("single asterisk") {
        TempFile t1({}, "temp-file.extension");
        TempFile t2({}, "temp-file.ext");
        auto result = globpp::glob("*.extension");
        REQUIRE(1 == result.size());
        REQUIRE("." + DIRSEP + "temp-file.extension" == result.at(0));
    }
    SECTION("multiple asterisks") {
        TempFile t1({}, "temp-file-a");
        TempFile t2({}, "temp-file");
        auto result = globpp::glob("*-*-*");
        REQUIRE(1 == result.size());
        REQUIRE(("." + DIRSEP + "temp-file-a") == result.at(0));
    }
    SECTION("question mark") {
        TempFile t1({}, "temp-file-a");
        TempFile t2({}, "temp-file-aa");
        auto result = globpp::glob("*-*-?");
        REQUIRE(1 == result.size());
        REQUIRE(("." + DIRSEP + "temp-file-a") == result.at(0));
    }
}

TEST_CASE("files in sub-directory", "[tests]") {
    TempFile dummdir({ "dummy" }, "");

    SECTION("explicit folder") {
        TempFile t1({ "dummy" }, "temp-file.extension");
        auto result = globpp::glob("." + DIRSEP + "dummy" + DIRSEP + "*.extension");
        REQUIRE(1 == result.size());
        REQUIRE("." + DIRSEP + "dummy" + DIRSEP + "temp-file.extension" == result.at(0));
    }
    SECTION("asterisk for folder") {
        TempFile t1({ "dummy" }, "temp-file.extension");
        auto result = globpp::glob("." + DIRSEP + "*" + DIRSEP + "*.extension");
        /* print_results(result); */
        REQUIRE(1 == result.size());
        REQUIRE("." + DIRSEP + "dummy" + DIRSEP + "temp-file.extension" == result.at(0));
    }
}

TEST_CASE("recursion", "[!mayfail][recursion]") {
    SECTION("recursive asterisk works.") {
        TempFile t1({ "dummy" }, "temp-file.extension");
        TempFile t2({ "d", "u" }, "temp-file.extension");
        TempFile t3({ "d", "u", "m" }, "temp-file.extension");

        // trick files!!
        TempFile t4({ "d", "u" }, "temp-file.ext");
        TempFile t5({ "d", "u", "m" }, "temp-file.ext");

        auto result = globpp::glob("." + DIRSEP + "**" + DIRSEP + "*.extension");
        /* print_results(result); */
        REQUIRE(3 == result.size());
        REQUIRE("." + DIRSEP + "dummy" + DIRSEP + "temp-file.extension" == result.at(0));
    }
}
