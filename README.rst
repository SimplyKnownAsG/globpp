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
1. Use ``execute_process`` and ``add_subdirectory``. This seems to be the easiest, but if there is a
   better way, let us know how and submit a patch.::

    # Recommend putting this into a `<root>/3rd-party/CMakeLists.txt`
    
    if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/globpp)
            execute_process(
                    COMMAND git clone https://github.com/SimplyKnownAsG/globpp.git
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/globpp/src ${CMAKE_CURRENT_BINARY_DIR}/globpp/build)


2. Use ``file(DOWNLOAD)``. This method is subject to change since the source files could change.::

    foreach(file_name CMakeLists.txt Glob.cpp Glob.hpp Iterator.cpp Iterator.hpp Search.cpp Search.hpp)
        file(DOWNLOAD
             https://raw.githubusercontent.com/SimplyKnownAsG/globpp/master/src/${file_name}
             ${CMAKE_CURRENT_SOURCE_DIR}/globpp/${file_name})
    endforeach(file_name)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/globpp)


3. Use ``ExternalProject_Add```. This is perhaps the most complicated option, and I guess if you
   really like ``globpp``, you might like that CMake expects you to actually install your external
   project dependencies.::

    include(ExternalProject)

    ExternalProject_Add(EXTERNAL_GLOBPP
        GIT_REPOSITORY "https://github.com/SimplyKnownAsG/globpp.git"
        GIT_TAG "origin/master"
        CMAKE_ARGS "-DGLOBPP_TESTS=OFF" "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/3rd-party"
        )

    # later, before your target
    link_directories("${CMAKE_BINARY_DIR}/3rd-party/lib")
    
    add_executable(<YOUR_TARGET> ${TEST_SOURCES})
    add_dependencies(<YOUR_TARGET> EXTERNAL_GLOBPP)
    target_link_libraries(<YOUR_TARGET> globpp)


Otherwise
---------
1. Download with ``wget``/``curl``
2. ``git clone``/``cmake -Bbuild -H.``/``cmake --build build --target install``

