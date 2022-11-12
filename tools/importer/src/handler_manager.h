#pragma once

#include "handler/base_handler.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

class handler_manager {
public:
  std::vector<std::shared_ptr<base_handler>> get_all();
  void register_handler(std::shared_ptr<base_handler> handler);

protected:
  std::vector<std::shared_ptr<base_handler>> m_handlers;
};
