#pragma once

#include "handler/base_handler.h"
#include <assimp/Importer.hpp>
#include <vector>
class mesh_handler : public base_handler {
public:
  std::string get_sub_command() override;
  void process(const std::string &path) override;

protected:
  typedef struct {
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
  } mesh_vertex;
  typedef struct {
    std::vector<mesh_vertex> vertices;
    std::vector<uint32_t> indices;
  } mesh_data;
  void output_mesh(const aiScene *scene, const std::string &path);
};
