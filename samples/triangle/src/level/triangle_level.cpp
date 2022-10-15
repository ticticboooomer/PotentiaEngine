#include "triangle_level.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/interface/shader.h"
#include <potentia-core/pch.h>

void triangle_level::setup()
{
  auto layout = hal_factory::instance()->create_pipeline_layout();
  m_vertices.push_back({0, -0.5, 0, 1});
  m_vertices.push_back({0.5, 0.5, 0, 1});
  m_vertices.push_back({-0.5, 0.5, 0, 1});
  layout->init_vertex_desc(sizeof(draw_vertex));
  m_vertexBuffer = hal_factory::instance()->create_buffer(sizeof(draw_vertex) * m_vertices.size(), buffer::usage::vertex);
  m_vertexBuffer->map(m_vertices.data());
  auto vert = layout->create_shader();
  auto frag = layout->create_shader();
  vert->set_type(shader::vertex);
  frag->set_type(shader::fragment);
  vert->init_from_file("assets/vert.spv");
  frag->init_from_file("assets/frag.spv");
  m_pipeline = hal_factory::instance()->create_pipeline(layout);
  m_commander = m_pipeline->get_commander();
}

void triangle_level::render()
{
  m_commander->begin();
  m_commander->bind_vertex_buffer(m_vertexBuffer.get());
  m_commander->draw(m_vertices.size());
  m_commander->end();
}

void triangle_level::tick()
{
}
