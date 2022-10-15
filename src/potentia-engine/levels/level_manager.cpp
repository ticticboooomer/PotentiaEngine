#include "level_manager.h"
#include <functional>
#include <map>
#include <memory>
#include <utility>

void level_manager::register_level(size_t id, std::function<g_level*()> level_fn) {
  if (registry == nullptr) {
    registry = std::make_shared<std::map<size_t, std::function<g_level*()>>>();
  }
  registry->insert(registry->end(), std::make_pair(id, level_fn));
}

void level_manager::load_level(size_t id) {
  // TODO pre-load a level without rendering it
}

void level_manager::present_level(size_t id) {
  auto level = registry->find(id);
  active = level->second();
  active->setup();
}

void level_manager::run_for_active(std::function<void (g_level*)> action) {
  action(active);
}
