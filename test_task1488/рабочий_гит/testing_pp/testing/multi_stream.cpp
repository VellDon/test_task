#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
// #include <boost/program_options.hpp>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdint> // для int64_t

int mult_stream(std::string &name_file)
{
    std::vector<std::ofstream> multi_str;
    int count_file = 0;
    std::ifstream name(name_file);
    if (!name.is_open())
    {
        spdlog::error("Не удалось открыть файл");
        return 1;
    }
    std::string line;
    std::getline(name, line);
    std::stringstream ss(line);
    std::string token;
    int count = 0;
    int count_rts = 0;
    int count_price = 0;
    while (std::getline(ss, token, ';'))
    {
        count++;
        if (token == "receive_ts")
        {
            count_rts = count;
        }
        if (token == "price")
        {
            count_price = count;
        }
    }
    int count_line = 0;
    std::vector<std::pair<int64_t, double>> data;
    while (std::getline(name, line))
    {
        count_line++;
        if (line.empty())
        {
            continue;
        }
        std::stringstream sss(line);

        int64_t time = 0;
        double price = 0.0;
        bool valid_row = true;
        count = 0;

        while (std::getline(sss, token, ';'))
        {
            count++;
            try
            {
                if (count == count_price)
                {
                    price = std::stod(token);
                }
                if (count == count_rts)
                {
                    time = std::stoll(token);
                }
            }
            catch (const std::exception &e)
            {
                spdlog::warn("Ошибка преобразования в файле {}: {} (строка: {})", name_file, e.what(), line);
                valid_row = false;
                break;
            }
        }
        if (valid_row)
        {
            data.emplace_back(time, price);
        }
        if (count_line > 5)
        {
            count_file++;
            std::stringstream temp;
            temp << "temp_file_" << count_file << ".txt";
            std::string temp_name = temp.str();

            std::sort(data.begin(), data.end(), [](auto &a, auto &b)
                      { return a.first < b.first; });
            std::ofstream file(temp_name);
            if (!file.is_open())
            {
                spdlog::error("ошибка создания файла");
                return 1;
            }
            for (auto &num : data)
            {
                std::string temp_num = std::format("{};{:.8f}", num.first, num.second);
                file << temp_num << "\n";
            }
            multi_str.emplace_back(temp_name);
            data.clear();
            count_line = 0;
        }
    }

    return 0;
}
int main()
{
    std::string s = "Trade.cvs";
    mult_stream(s);
}