#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int write_file(double num, int64_t time, std::string output)
{
    std::ofstream file(output);
    file << time << ";" << num << "\n";
    return 0;
}