#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/median.hpp>

using namespace boost::accumulators;

int main()
{
    // Используем extended_p_square для большей точности на малых выборках
    // Но даже он на 2-3 числах может давать погрешность, так как это СТАТИСТИКА
    accumulator_set<double, stats<tag::median>> acc;
    std::ofstream file("res.txt");
    // Устанавливаем фиксированный формат и 8 знаков после запятой для файла
    file << std::fixed << std::setprecision(8);
    double med = 0.0;
    double new_median = 0.0;
    for (double i = 0.0; i < 10000000.0; i += 0.5)
    {
        if (i == 0.0)
        {
            med = 0.0;
        }
        else
        {
            acc(static_cast<double>(i));

            if (med != median(acc))
            {
                file << "Число: " << i << " | Медиана Boost: " << median(acc) << std::endl;
                med = median(acc);
            }
        }
    }
    return 0;
}