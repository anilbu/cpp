#ifndef FSTREAM_HELPER_H
#define FSTREAM_HELPER_H

#include <random>
#include <string>
#include <iostream>
#include <set>
#include <forward_list>
#include <utility>
#include <fstream>

std::ifstream open_text_file(std::string& filename) {
    std::ifstream ifs {filename};
    
    return ifs;
}

#endif