#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> read_list_dir(const std::string &path, std::vector<std::string> masks)
{
    std::cout << "Вошли в функцию поиска файлов" << std::endl;
    fs::path dir = path;
    std::vector<std::string> list_file;
    for (const fs::directory_entry &entry : fs::directory_iterator(dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".cvs") // только обычные файлы
        {
            std::cout << entry.path().filename() << std::endl;
            std::string filename = entry.path().filename().string();
            if (!masks.empty())
            {
                for (auto &title : masks)
                {
                    if (filename.find(title) != std::string::npos)
                    {
                        list_file.push_back(entry.path().filename());
                    }
                }
            }
            else
            {
                list_file.push_back(entry.path().filename());
            }
        }
    }
    std::cout << "нашли список подходящих" << std::endl;
    return list_file;
}