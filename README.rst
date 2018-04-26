======
globpp
======

``globpp`` is c++ header and source file for globbing files and directories.

.. image:: https://travis-ci.org/SimplyKnownAsG/globpp.svg?branch=master
    :target: https://travis-ci.org/SimplyKnownAsG/globpp


.. image:: https://ci.appveyor.com/api/projects/status/github/SimplyKnownAsG/globpp?branch=master&svg=true
    :target: https://ci.appveyor.com/project/SimplyKnownAsG/globpp

.. contents:: Table of Contents
    :backlinks: top


Quickstart
==========

::

    #include "globpp.hpp"

    int main(int argc, char* argv[]) {
        std::vector<std::string> names = globpp::glob("*.cpp");
    }

Getting the code
================

CMake
-----
# use ``file(DOWNLOAD)``
# use subproject

Otherwise
---------
# download with wget/curl
# clone/build

