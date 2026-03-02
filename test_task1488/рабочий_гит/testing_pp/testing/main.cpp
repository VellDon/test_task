#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>
#include <algorithm>
#include "toml++/toml.h"
#include "parsing.h"
#include "read_directory.h"
#include "open_file.h"
#include "median.h"
#include "ParseResult.h"

//========================================================//
/* Флаги компиляции и линоквки для логов g++ main.cpp -lboost_program_options -lspdlog -lfmt */

// namespace po = boost::program_options;
int main(int argc, char *argv[])
{
    /*Шаг 1 - парсим аргументы, регистрируем флаги,
    Устанавливаем переменные для парсинга
    Если флага нет устаналиваем переменную по умолчанию
    если неверно указана строка аргументов завершаем*/

    auto res = Parsing(argc, argv);
    if (res.has_error)
    {
        return 1;
    }
    if (res.show_help)
    {
        return 0;
    }

    /* Шаг 2 - настройка конфигурации и проверки данных .toml */

    toml::table table;

    // -----------------------проверка файла------------------------------------

    try
    {
        table = toml::parse_file(res.name_file_config);
    }
    catch (const toml::parse_error &err)
    {
        spdlog::error("Ошибка файла .toml: {} ", err.what());
        return 1;
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

    //  ----------------------достаем секцию [main] и [input]-------------------------------------

    auto main_table = table["main"].as_table();

    if (!main_table)
    {
        spdlog::error("отсутствует секция main в .toml");
        return 1;
    }

    if (!main_table->contains("input"))
    {
        spdlog::error("отсутствует input в .toml");
        return 1;
    }

    auto input_ptr = main_table->get_as<std::string>("input");

    if (!input_ptr)
    {
        spdlog::error("Параметр input должен быть строкой");
        return 1;
    }

    std::string input = input_ptr->get();

    if (!std::filesystem::exists(input) || !std::filesystem::is_directory(input))
    {
        spdlog::error("Директория input не существует или не является директорией: {}", input);
        return 1;
    }
    spdlog::info("input = {}", input);

    //------------------------настриваем output и маски--------------------------------------

    auto mask_array = main_table->get_as<toml::array>("filename_mask");

    std::vector<std::string> masks;

    if (!mask_array || mask_array->empty())
    {
        spdlog::info("отсутствуют маски");
    }
    else
    {
        for (auto &el : *mask_array)
        {
            if (el.is_string())
            {
                auto s = el.value<std::string>();
                masks.push_back(*s);
            }
            else
            {
                spdlog::error("имя маски должен быть string");
                return 1;
            }
        }
    }

    spdlog::info("Выбранные маски для файлов:");
    for (auto &name : masks)
    {
        std::cout << "-" << name << std::endl;
    }

    std::string output = "./output";
    if (auto output_ptr = main_table->get_as<std::string>("output"))
    {

        output = output_ptr->get();
    }
    else
    {
        spdlog::warn("Отсутствует параметр output, используем дефолт {}", output);
    }

    if (!std::filesystem::exists(output) || !std::filesystem::is_directory(output))
    {
        spdlog::info("Выбраной output директории не существует - {}", output);
        try
        {
            fs::create_directories(output);
            spdlog::info("Создаем новую директорию {}", output);
        }
        catch (const fs::filesystem_error &e)
        {
            spdlog::error("Ошибка создания директрии output - {}", e.what());
            return 1;
        }
    }

    spdlog::info("выбраный output - {}", output);

    // 3 блок поиск подходящих файлов
    // находим все файлы в директории соответствуещие критериям масок и формату
    auto list_file = read_list_dir(input, masks);
    if (list_file.empty())
    {
        spdlog::error("Отсутствуют файлы для подсчета медианы");
        return 1;
    }

    // 4 Открытие файла перенос данных в вектор сортировка по времени
    std::vector<std::pair<int64_t, double>> all_data;
    for (auto &name_file : list_file)
    {
        std::vector<std::pair<int64_t, double>> data = open_file(name_file);
        all_data.insert(all_data.end(), data.begin(), data.end());
    }
    std::sort(all_data.begin(), all_data.end(), [](auto &a, auto &b)
              { return a.first < b.first; });

    mediana(all_data, output);

    return 0;
}