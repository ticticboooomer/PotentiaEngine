#pragma once
#include "potentia-hal/interface/commander.h"
#include "potentia-hal/vulkan/vk_pipeline.h"
#include "potentia-structure/g_level.h"
#include <potentia-core/pch.h>
#include "potentia-hal/interface/buffer.h"
#include "structs/vertex.h"


class triangle_level : public g_level {
public:
  void setup();
  void tick();
  void render();
protected:
  std::shared_ptr<pipeline> m_pipeline;
  std::shared_ptr<commander> m_commander;
  std::vector<draw_vertex> m_vertices;
  std::shared_ptr<buffer> m_vertexBuffer;
};
