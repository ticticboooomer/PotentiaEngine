#include "engine_runtime.h"
#include "potentia-hal/hal_factory.h"
#include <memory>

engine_runtime::engine_runtime() { hal_factory::instance()->initialize(); }

void engine_runtime::run() { hal_factory::instance()->run(); }

std::shared_ptr<engine_runtime> engine_runtime::create_instance() {
  return std::make_shared<engine_runtime>();
}
