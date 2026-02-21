#include <vector>
#include <string>
#include <cstdint>   // для int64_t
#include <algorithm> // для sort
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::pair<int64_t, double>> open_file(std::string name_file)
{
    std::cout << "Вошли в функцию сбора в массив и сортировке" << std::endl;

    std::ifstream file(name_file);
    std::string line;
    std::getline(file, line);
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
    std::vector<std::pair<int64_t, double>> data;
    int64_t receive_ts;
    double price;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::stringstream sss(line);
        count = 0;
        while (std::getline(sss, token, ';'))
        {
            count++;
            if (count == count_price)
            {
                price = std::stod(token);
            }
            if (count == count_rts)
            {
                receive_ts = std::stoll(token);
            }
        }
        data.emplace_back(receive_ts, price);
    }

    return data;
}