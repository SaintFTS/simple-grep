#include "grep_lite.h"

int main(int argc, char** args){
    if (argc<2) return -1;
    char* str_to_find = args[1];
    std::vector<std::filesystem::path> files_ext;
    if (argc == 3) SURROUNDING_COLS_AMOUNT = std::atoi(args[argc-1]); //files_ext.push_back(std::string(args[2]));

    auto exe_path = std::filesystem::current_path();
    auto files = GetFilesInDirectory(exe_path);

    GetStringFromFiles(files, str_to_find, files_ext);
}
