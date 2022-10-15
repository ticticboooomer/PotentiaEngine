#pragma once

#include "common.h"
#include "processor/AssetFileProcessor.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <memory>

class ModelFileProcessor : public AssetFileProcessor {
public:
  bool IsFileType(const std::string &file) override;
  TaggedBundleSegment Process(const std::string& file) override;

protected:
  const aiScene* load_scene(const std::string& string);
  BundleRecord LoadMesh(aiMesh *mesh);
  int PackColor(float r, float g, float b, float a);
};
