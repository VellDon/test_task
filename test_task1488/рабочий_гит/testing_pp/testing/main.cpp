#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>
#include "toml++/toml.h"
#include "parsing.h"
#include "read_directory.h"
#include "open_file.h"
#include "median.h"

//========================================================//
/* Флаги компиляции и линоквки для логов -lspdlog -lfmt */

namespace po = boost::program_options;
int main(int argc, char *argv[])
{
    /*Шаг 1 - парсим аргументы, регистрируем флаги,
    Устанавливаем переменные для парсинга
    Если флага нет устаналиваем переменную по умолчанию
    если неверно указана строка аргументов завершаем*/

    std::string name_file_config = Parsing(argc, argv);

    /* Шаг 2 - настройка конфигурации */

    toml::table table;
    try
    {
        table = toml::parse_file(name_file_config);
    }
    catch (const toml::parse_error &err)
    {
        spdlog::error("Ошибка файла .toml: {} ", err.what());
        return 1; //  завершение программы
    }
    catch (const std::exception &err)
    {
        spdlog::error("Ошибка при чтении конфигурации: {}", err.what());
        return 1;
    }

    if (table.empty())
    {
        spdlog::error("Empty file configuration");
        return 1;
    }

    auto main_table = table["main"].as_table();
    auto mask_array = (*main_table)["filename_mask"].as_array(); // filename_mask → массив
    std::vector<std::string> masks;

    for (auto &el : *mask_array)
    {
        masks.push_back(el.value<std::string>().value_or("none"));
    }

    std::cout << "СПИСОК ИМЕН ИХ КОНФИГА:" << std::endl;
    for (auto &name : masks)
    {
        std::cout << "-" << name << std::endl;
    }

    auto input = table["main"]["input"].value_or("./");
    auto output = table["main"]["output"].value_or("out.cvs");

    // 3 блок поиск подходящих файлов
    std::vector<std::string> list_file = read_list_dir(input, masks);

    // 4 Открытие файла перенос данных в вектор сортировка по времени
    for (auto &name_file : list_file)
    {
        std::vector<std::pair<int64_t, double>> data = open_file(name_file);
        mediana(data, output);
    }

    return 0;
}