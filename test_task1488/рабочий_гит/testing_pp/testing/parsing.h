#include <iostream>
#include <boost/program_options.hpp>
#include "ParseResult.h"

namespace po = boost::program_options;

ParseResult Parsing(const int argc, char *argv[])
{
    ParseResult res;
    po::options_description desc("Options");
    desc.add_options()("config", po::value<std::string>(&res.name_file_config)->default_value("config.toml"), "file conf path")("cfg", po::value<std::string>(&res.name_file_config), "file conf path")("help,h", "help information");
    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (const po::error &e)
    {
        spdlog::error("Ошибка флагов или аргументов: {}", e.what());
        std::cerr << desc << "\n";
        res.has_error = true;
        return res;
    }
    if (vm.count("help"))
    {
        spdlog::info("info line arg.");
        std::cerr << desc << "\n";
        res.show_help = true;
        return res;
    }
    spdlog::info("Используется конфигурация: {}", res.name_file_config);
    return res;
}