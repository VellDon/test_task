#include <iostream>
#include <thread>
#include <vector>
#include "toml++/toml.h"


int main()
{
    try {
        auto config = toml::parse_file("config.toml");
        auto set_1 = config["nomain"];
        auto set_2 = config[main];
    }
    
    std::cout << "_____________S_T_A_R_T_____________" << std::endl;
    std::cout << set_1.



}