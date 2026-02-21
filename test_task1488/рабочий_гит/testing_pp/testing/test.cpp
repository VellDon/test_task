#include <vector>
#include <iostream>
#include <queue>

int main()
{
    std::vector<int> mass = {1, 3, 4, 7, 8, 10, 89, 90};
    std::priority_queue<int> max_heap;
    std::priority_queue<int> min_heap;
    for (const auto &num : mass)
    {
        if (max_heap.size() < 0 && min_heap.size() < 0)
        {
            min_heap.push(num);
            continue;
        }
        if ()
    }
    return 0;
}