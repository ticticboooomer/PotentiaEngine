#include "level/triangle_level.h"
#include "potentia-engine/engine_runtime.h"
#include "potentia-engine/levels/level_manager.h"
#include <memory>
#include "potentia-core/pch.h"
int main() {
  level_manager::instance()->register_level(0,
                                            []() { return new triangle_level(); });
  auto runtime = std::make_shared<engine_runtime>();
  level_manager::instance()->present_level(0);
  runtime->run();
}
