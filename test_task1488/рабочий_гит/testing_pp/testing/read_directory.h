#include <filesystem>
#include <iostream>
#include <vector>
#include <set>
#include <spdlog/spdlog.h>
namespace fs = std::filesystem;

std::set<std::string> read_list_dir(const std::string &path, std::vector<std::string> masks)
{
    spdlog::info("Вошли в функцию поиска файлов");
    fs::path dir = path;
    std::set<std::string> list_file;
    
    for (const fs::directory_entry &entry : fs::directory_iterator(dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") // только обычные файлы
        {
            std::string filename = entry.path().filename().string();
            spdlog::info("Обрабатываемый файл - {}", filename);
            if (!masks.empty())
            {
                for (auto &title : masks)
                {
                    if (filename.find(title) != std::string::npos)
                    {
                        //list_file.insert(entry.path().filename());
                        list_file.insert(entry.path().string());
                        std::cout << entry.path().string() << std::endl;
                        break;
                    }
                }
            }
            else
            {
                //list_file.insert(entry.path().filename());
                list_file.insert(entry.path().string());
            }
        }
    }
    spdlog::info("нашли список подходящих");
    return list_file;
}