#ifndef UTIL_HPP
#define UTIL_HPP

#include "xcp.hpp"

std::string get_file_part(const std::string path);
bool is_directory(const std::string path);
bool is_file(const std::string path);
std::string append_file_to_path(const std::string path, const std::string file);
std::string make_human_readable(long long unsigned number);



#endif//UTIL_HPP
