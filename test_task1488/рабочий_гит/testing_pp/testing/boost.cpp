#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <spdlog/spdlog.h>

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    /*Шаг 1 - парсим аргументы, регистрируем флаги,
    Устанавливаем переменные для парсинга
    Если флага нет устаналиваем переменную по умолчанию
    если неверно указана строка аргументов завершаем*/

    std::string name_file_config;
    po::options_description desc("Options");
    desc.add_options()
        ("config,cnf", po::value<std::string>(&name_file_config)->default_value("config.toml"), "file conf path");

    po::variables_map vm;

    try{
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }catch(const po::error& e){
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << desc << "\n"; // покажет все допустимые опции
        return 1;


    }
    


    spdlog::info("Это информационное сообщение");
    spdlog::warn("Это предупреждение");
    spdlog::error("Ошибка: {} + {} = {}", 1, 2, 1+2);

    return 0;
}