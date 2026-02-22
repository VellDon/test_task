#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

std::string Parsing(const int argc, char *argv[])
{
    std::string name_file_config;
    po::options_description desc("Options");
    desc.add_options()("config", po::value<std::string>(&name_file_config)->default_value("config.toml"), "file conf path")("cfg", po::value<std::string>(&name_file_config), "file conf path")("help,h", "help information");
    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (const po::error &e)
    {
        spdlog::error("Ошибка флагов или аргументов");
        std::cerr << desc << "\n";
        exit(1);
    }
    if (vm.count("help"))
    {
        spdlog::info("info line arg.");
        std::cerr << desc << "\n";
    }
    return name_file_config;
}