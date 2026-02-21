#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>
#include "write_file.h"

int mediana(const std::vector<std::pair<int64_t, double>> &mass, const std::string &output_file)
{
    std::priority_queue<double> min_heap;
    std::priority_queue<double, std::vector<double>, std::greater<double>> max_heap;
    double old_median = 0.0;
    double new_median = 0.0;

    std::ofstream file(output_file, std::ios::app);

    for (const auto &num : mass)
    {
        if (max_heap.empty() && min_heap.empty())
        {
            min_heap.push(num.second);
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
        if (max_heap.size() > min_heap.size() && max_heap.size() - min_heap.size() == 2)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        else if (min_heap.size() > max_heap.size() && min_heap.size() - max_heap.size() == 2)
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
        // Тут будет функция записи
        if (old_median != new_median)
        {
            file << num.first << ";" << num.second << "\n";
            old_median = new_median;
        }
    }

    return 0;
}