#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>
#include <algorithm>
#include <fstream>
#include <sstream>

int mult_stream(const std::string &name_file){
  std::vector<std::ifstream> files;
  std::ifstream name(name_file);
  if(!name.is_open()){
    spdlog::error("Не удалось открыть файл -{}", name);
    return 1;
  }
  std::string line;
  int count = 0;
  int count_file = 0;
  
  while(std::getline(name, line)){
    if(count == 0){
        count_file++;
        std::stringstream ss;
        ss << "temp_file_" << count_file;
    }
    if(count == 0){

    }

  }


}