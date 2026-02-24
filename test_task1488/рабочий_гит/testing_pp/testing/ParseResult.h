#pragma once
#include <string>
struct ParseResult
{
    std::string name_file_config;
    bool has_error = false;
    bool show_help = false;
};