#include <vector>
#include <iostream>
#include <queue>
#include <functional> 

int main()
{
    std::vector<int> mass = {1, 3, 4, 7, 8, 10, 89, 90};
    std::priority_queue<int> min_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> max_heap;

    for (const auto &num : mass)
    {
        if (max_heap.empty() && min_heap.empty())
        {
            min_heap.push(num);
            continue;
        }
        if (num <= min_heap.top()){
            min_heap.push(num);
        }else {
            max_heap.push(num);
        }
        if (max_heap.size() > min_heap.size() && max_heap.size() - min_heap.size() == 2){
            min_heap.push(max_heap.top());
            max_heap.pop();

        }else if (min_heap.size() > max_heap.size() && min_heap.size() - max_heap.size() == 2){
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
        if (max_heap.size() == min_heap.size()){
            std::cout << "медиана = " << (max_heap.top() + min_heap.top()) / 2 << std::endl;
        }else {
            if (max_heap.size() > min_heap.size()){
                std::cout << "медиана = " << max_heap.top() << std::endl;
            }else {
                std::cout << "медиана = " << min_heap.top() << std::endl;
            }
        }

    }
    // Тут печать для теста
    std::vector<int> res;
    while(!min_heap.empty()){
        //std::cout << min_heap.top() << " ";
        res.push_back(min_heap.top());
        min_heap.pop();
    }

    for (int i = res.size() - 1; i >= 0; --i)
        std::cout << res[i] << " ";
    
    while(!max_heap.empty()){
        std::cout << max_heap.top() << " ";
        max_heap.pop();
    }

    
    return 0;
}