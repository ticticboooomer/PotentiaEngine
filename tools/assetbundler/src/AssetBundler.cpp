#include "AssetBundler.h"
#include "processor/model/ModelFileProcessor.h"
#include <fstream>
#include <memory>
#include "io/file_manager.h"

void AssetBundler::Setup() {
  m_agents.push_back(std::make_shared<ModelFileProcessor>());
}

void AssetBundler::Run() {
  auto files = file_manager::enumerate(m_directory);
  for (const auto& path : files) {
    for (const auto& agent : m_agents) {
      if (agent->IsFileType(path.abs_path)){
        auto result = agent->Process(path.abs_path);
        populate_bundle(&result);
      }
    }
  }
}

void AssetBundler::Output() {
  std::ofstream fs;
  fs.open("bundle_test.pobu");
  for (auto & bundle : m_bundles){
    auto record = bundle.second;
    fs.write(record.c_str(), record.length());
  }
  fs.close();
}

void AssetBundler::populate_bundle(TaggedBundleSegment* segment) {
  for (auto & record : *segment) {
    m_bundles.push_back(record.second);
  }
}
