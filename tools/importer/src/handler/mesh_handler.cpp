#include "mesh_handler.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
std::string mesh_handler::get_sub_command() { return "mesh"; }

void mesh_handler::process(const std::string &path) {
  Assimp::Importer importer;

  const aiScene *scene =
      importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_FlipUVs |
                                  aiProcess_JoinIdenticalVertices);
  output_mesh(scene, path);
}

void mesh_handler::output_mesh(const aiScene *scene, const std::string &path) {
  if (!scene->HasMeshes()) {
    throw new std::exception("No Meshes found in given file");
  }
  auto dir_path = path + ".exports/";
  std::filesystem::create_directory(dir_path);

  for (size_t i = 0; i < scene->mNumMeshes; i++) {
    auto mesh = scene->mMeshes[i];
    if (!mesh->HasPositions()) {
      continue;
    }
    mesh_data data;
    data.vertices.resize(mesh->mNumVertices);
    for (size_t v = 0; v < mesh->mNumVertices; v++) {
      auto vertex = mesh->mVertices[v];
      auto normal = mesh->mNormals[v];
      data.vertices[v] = {vertex.x, vertex.y, vertex.z,
                          normal.x, normal.y, normal.z};
    }

    std::string output_str = (char *)data.vertices.size();
    output_str += (char *)data.vertices.data();

    auto model_out = dir_path + mesh->mName.C_Str() + ".p_mesh";
    std::ofstream out_file;
    out_file.open(model_out);
    out_file.write(output_str.c_str(), output_str.size());
    out_file.close();
  }
}
