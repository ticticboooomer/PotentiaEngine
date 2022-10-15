#include "common.h"
#include <iostream>
#include <ctime>

size_t RES_ID_COUNTER = 0;

std::string MakeResourceKey(std::string path) {
  return "res:"+ path + ":" + std::to_string(++RES_ID_COUNTER);
}

const std::string APP_NAME = "Potentia Asset Bundler"; 

void Log(const std::string& log) {
  std::cout << "[" << APP_NAME << "]" << "[" << std::time(0) << "]>> " << log << std::endl;
}
