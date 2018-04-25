#pragma once

#include <cstdio>
#include <fstream>
#include <stack>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#ifdef _WIN32
const std::string DIRSEP = "\\";
#else
const std::string DIRSEP = "/";
#endif

class TempFile {
private:
    std::stack<std::string> folders;
    std::string filename;

public:
    TempFile(std::vector<std::string> folder_names, std::string name) {
        std::string full_name;
        for (auto& folder : folder_names) {
            full_name += folder + DIRSEP;
            this->folders.push(full_name);
            mkdir(full_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        this->filename = full_name + name;

        // write the file...
        std::ofstream tempfile(this->filename.c_str());
        tempfile << "this is a temporary file used for testing, it should be deleted.\n";
        tempfile.close();
    };

    ~TempFile() {
        std::remove(this->filename.c_str());
        while (!this->folders.empty()) {
            auto& folder = this->folders.top();
            rmdir(folder.c_str());
            this->folders.pop();
        }
    };
};
