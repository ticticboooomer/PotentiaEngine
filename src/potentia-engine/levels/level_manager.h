#pragma once
#include "potentia-core/base/global_singleton.h"
#include "potentia-structure/g_level.h"
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <potentia-core/pch.h>

class level_manager : public global_singleton<level_manager> {
public:
  void register_level(size_t id, std::function<g_level*()> level);
  void load_level(size_t id);
  void present_level(size_t id);
  void run_for_active(std::function<void(g_level*)> action);
protected:
  g_level* active;
  std::shared_ptr<std::map<size_t, std::function<g_level*()>>> registry;
};
