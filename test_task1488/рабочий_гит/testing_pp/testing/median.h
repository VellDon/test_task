#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>

int mediana(const std::vector<std::pair<int64_t, double>> &mass, const std::string &output_file)
{
    std::priority_queue<double> min_heap;
    std::priority_queue<double, std::vector<double>, std::greater<double>> max_heap;

    fs::path dir = output_file;
    try{
    if(!fs::exists(dir)){
        fs::create_directories(dir);
        spdlog::info("Создаем новую директорию {}", dir.string());
    }
    }catch(const fs::filesystem_error& e){
        spdlog::error("Ошибка создания директрии output - {}", e.what());
        return 1;
    }
    std::ofstream file(dir / "median_result.csv");
    if(!file.is_open()){
        spdlog::error("Не удалось создать файл - median_result.csv");
        return 1;
    }
    double old_median = 0.0;
    double new_median = 0.0;
    for (const auto &num : mass)
    {
        if (max_heap.empty() && min_heap.empty())
        {
            min_heap.push(num.second);
            new_median = num.second;
            file << num.first << ";" << new_median << "\n";
            old_median = new_median;
            
            continue;
        }
        if (num.second <= min_heap.top())
        {
            min_heap.push(num.second);
        }
        else
        {
            max_heap.push(num.second);
        }
        if (max_heap.size() > min_heap.size() && max_heap.size() - min_heap.size() > 1)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        else if (min_heap.size() > max_heap.size() && min_heap.size() - max_heap.size() > 1)
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
        if (max_heap.size() == min_heap.size())
        {
            new_median = (max_heap.top() + min_heap.top()) / 2;
        }
        else
        {
            if (max_heap.size() > min_heap.size())
            {
                new_median = max_heap.top();
            }
            else
            {
                new_median = min_heap.top();
            }
        }
        
        if ((std::abs(old_median - new_median) > 1e-9))
        {
            file << num.first << ";" << new_median << "\n";
            old_median = new_median;
        }
    }

    return 0;
}
