#include "catch.hpp"

#include "TempFile.hpp"
#include "globpp.hpp"

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
        auto result = globpp::glob("./dummy/*.extension");
        REQUIRE(1 == result.size());
        REQUIRE("." + DIRSEP + "dummy" + DIRSEP + "temp-file.extension" == result.at(0));
    }
    SECTION("asterisk for folder does not work") {
        TempFile t1({ "dummy" }, "temp-file.extension");
        auto result = globpp::glob("./*/*.extension");
        REQUIRE(0 == result.size());
    }
}

TEST_CASE("recursion", "[!shouldfail][recurision]") {
    SECTION("recursive asterisk works.") {
        TempFile t1({ "dummy" }, "temp-file.extension");
        auto result = globpp::glob("./**/*.extension");
        REQUIRE(1 == result.size());
        REQUIRE("." + DIRSEP + "dummy" + DIRSEP + "temp-file.extension" == result.at(0));
    }
}
