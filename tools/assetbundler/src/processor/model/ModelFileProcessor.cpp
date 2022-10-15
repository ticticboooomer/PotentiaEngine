#include "ModelFileProcessor.h"
#include "common.h"
#include "structures/Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <stdlib.h>
#include <string>
#include <utility>
bool ModelFileProcessor::IsFileType(const std::string &file) {
  return load_scene(file) != nullptr;
}

const aiScene* ModelFileProcessor::load_scene(const std::string& string) {
  Assimp::Importer importer;
  auto scene = importer.ReadFile(
      string, aiProcess_CalcTangentSpace | aiProcess_FlipUVs |
                aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
  return scene;
}


TaggedBundleSegment ModelFileProcessor::Process(const std::string& file) {
  auto scene = load_scene(file);

  TaggedBundleSegment result;
  if (scene->HasMeshes()) {
    for (int i = 0; i < scene->mNumMeshes; i++) {
      auto output = LoadMesh(scene->mMeshes[i]);
      result.push_back(std::make_pair(BundleType::Mesh, output));
    }
  }
  return result;
}

BundleRecord ModelFileProcessor::LoadMesh(aiMesh *mesh) {
  std::string bOut = "";

  if (!mesh->HasPositions()) {
    Log("No Mesh found in model file");
    exit(1);
  }

  std::vector<Vertex> vertices;
  vertices.reserve(mesh->mNumVertices);
  for (size_t i = 0; i < mesh->mNumVertices; i++) {
    Vertex v;
    auto av = mesh->mVertices[i];
    v.position = {av.x, av.y, av.z};
    if (mesh->HasVertexColors(0)) {
      auto ac = mesh->mColors[i][0];
      v.color = PackColor(ac.r, ac.g, ac.b, ac.a);
    } else {
      v.color = PackColor(0, 0, 0, 0);
    }
    if (mesh->HasTextureCoords(0)) {
      auto at = mesh->mTextureCoords[i][0];
      v.textCoord = {at.x, at.y};
    } else {
      v.textCoord = {0, 0};
    }
    auto an = mesh->mNormals[i];
    v.normals = {an.x, an.y, an.z};
    auto at = mesh->mTangents[i];
    v.tangents = {at.x, at.y, at.z};
    bOut += reinterpret_cast<char *>(&v);
  }
  return std::make_pair(mesh->mName.C_Str(), bOut);
}

int ModelFileProcessor::PackColor(float r, float g, float b, float a) {
  int ri = r * 255;
  int gi = g * 255;
  int bi = b * 255;
  int ai = a * 255;

  return (ri << 24) + (gi << 16) + (bi << 8) + ai;
}
