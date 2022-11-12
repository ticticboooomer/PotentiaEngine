#include "handler_manager.h"
#include <memory>
#include <vector>

std::vector<std::shared_ptr<base_handler>> handler_manager::get_all() {
  return m_handlers;
}

void handler_manager::register_handler(std::shared_ptr<base_handler> handler) {
  m_handlers.push_back(handler);
}
