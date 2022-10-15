#pragma once

#include "potentia-hal/hal_storage.h"
#include "potentia-hal/interface/pipeline.h"
#include "potentia-hal/interface/pipeline_layout.h"
#include <memory>
#include <potentia-core/base/global_singleton.h>
#include <potentia-core/pch.h>
#include "potentia-hal/interface/buffer.h"

class hal_factory : public hal_storage<hal_factory> {
public:
  void initialize();
  void destroy();
  void run();
  std::shared_ptr<pipeline_layout> create_pipeline_layout();
  std::shared_ptr<buffer> create_buffer(size_t size, buffer::usage usg);
  std::shared_ptr<pipeline> create_pipeline(std::shared_ptr<pipeline_layout> layout);

protected:
  std::vector<std::shared_ptr<pipeline>> m_pipelines;
};
