#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#pragma once

//#define SURROUNDING_COLS_AMOUNT 5
static int SURROUNDING_COLS_AMOUNT = 2;

using str_line = std::pair<std::string, size_t>;

inline void shift_lines(std::vector<str_line>& vec, str_line str_to_insert);

inline std::vector<std::filesystem::path> GetFilesInDirectory(std::filesystem::path exe_path){
    std::vector<std::filesystem::path> files;
    for (const auto& path : std::filesystem::directory_iterator(exe_path)){
        files.push_back(path);
    }

    return files;
}
inline void GetStringFromFiles(std::vector<std::filesystem::path> files, const std::string& str_to_find, std::vector<std::filesystem::path>& extensions){
    std::vector<str_line> lines(SURROUNDING_COLS_AMOUNT*2+1);
    bool breakout = false;
    std::filesystem::path matching_file;
    for (int i = 0; i < files.size(); i++){
    lines.clear();
    lines.resize(SURROUNDING_COLS_AMOUNT*2+1); 

        std::ifstream file(files[i]);
        if (file.is_open()){
            std::string line;
            for (size_t line_num = 1; std::getline(file, line); line_num++ ) {
                if (line.find(str_to_find) != std::string::npos){
                    lines[SURROUNDING_COLS_AMOUNT] = str_line(line + " <<<",line_num); line_num++;        // Set the line in the middle of the set of lines
                        for (int k = 0; std::getline(file, line) && k < SURROUNDING_COLS_AMOUNT; k++) {
                            lines[SURROUNDING_COLS_AMOUNT+1+k] = str_line(line + " ",line_num); line_num++;
                    }
                    matching_file = files[i];

                    breakout = true;
                    break;
                }
                if (line_num-1>=SURROUNDING_COLS_AMOUNT){
                    shift_lines(lines, str_line(line, line_num));
                } else {
                    lines[line_num-1] = str_line(line + " ", line_num);
                }
            }
            file.close();
            if (breakout) break;
        }
    }
    if (lines[SURROUNDING_COLS_AMOUNT].first.empty()){
        std::cout << "Couldn't find string you provided." << std::endl;
        return;
    }

    std::cout << matching_file.string() << "\n\n";
    for (const auto& l : lines){
        if (!l.first.empty())
            std::cout << l.second << ". \t" << l.first << '\n';
    }
}
inline void shift_lines(std::vector<str_line>& vec, str_line str_to_insert){
    for (int i = 0; i < SURROUNDING_COLS_AMOUNT-1; i++) {
        vec[i] = std::move(vec[i+1]);
    }
    vec[SURROUNDING_COLS_AMOUNT-1] = str_to_insert;
}
/*
        {
            bool match = false;
            if (!extensions.empty()){
                for (int j = 0; j < extensions.size(); j++) {
                    if (extensions[i] == files[i].extension()){
                        match=true;
                    }
                }
                if (match==false) break;
            }
        }
        EXTENSIONS FEATURE IS CURRENTLY UNAVAILABLE
        */    
