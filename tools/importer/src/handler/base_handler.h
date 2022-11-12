#pragma once

#include <string>
class base_handler {
public:
  virtual std::string get_sub_command() = 0;
  virtual void process(const std::string &path) = 0;
};
